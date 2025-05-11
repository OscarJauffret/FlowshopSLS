//
// Created by Oscar Jauffret on 21/04/2025.
//

#include "../../include/core/flowShopMemetic.hpp"
#include "../../include/initialization/initialization.hpp"
#include "../../include/utils/slsTimeLimitProvider.hpp"
#include "../../include/core/flowShopII.hpp"
#include "../../include/core/flowShopVnd.hpp"
#include "../../include/core/flowShopTabuSearch.hpp"
#include "../../include/config/flowShopConfig.hpp"
#include "../config.hpp"
#include <iostream>
#include <set>
#include <chrono>

namespace chrono = std::chrono;

using std::endl;
using std::cout;
using chrono::steady_clock;

FlowShopMemetic::FlowShopMemetic(const Instance& instance, int populationSize, float mutationRate, LocalSearchMethod localSearchMethod,
                                 std::mt19937 rng)
    : populationSize(populationSize), mutationRate(mutationRate), rng(rng),
      numParentPieces(config::memetic::getNumCuts(instance.jobs)) {
    maxExecutionTime = SLSTimeLimitProvider::getAllowedTime(instance.jobs);

    // Initialize the population with srz solutions
    for (int i = 0; i < populationSize; i++) {
        Solution solution = initialization::simplifiedRZ(instance, rng);
        population.push_back(solution);
    }

    initializeLocalSearchFunction(instance, localSearchMethod);
    crossoverOrthogonalArray = generateOrthogonalArray(numParentPieces);
    mutationOrthogonalArray = config::memetic::getMutationOrthogonalArray();
}

void FlowShopMemetic::initializeLocalSearchFunction(const Instance &instance, LocalSearchMethod localSearchMethod) {
    switch (localSearchMethod) {
        case LocalSearchMethod::II: {
            auto solver = std::make_shared<FlowShopII>(instance, NeighbourhoodStructure::INSERT,
                                                       PivotingRule::FIRST_IMPROVEMENT, InitializationMethod::RANDOM,
                                                       rng);
            localSearch = [solver](const Solution& s, int timeMs) { return solver->run(s, timeMs); };
            break;
        }
        case LocalSearchMethod::VND: {
            auto solver = std::make_shared<FlowShopVND>(instance, VNDStrategy::TEI, rng);
            localSearch = [solver](const Solution& s, int timeMs) { return solver->run(s, timeMs); };
            break;
        }
        case LocalSearchMethod::TABU_SEARCH: {
            auto solver = std::make_shared<FlowShopTabuSearch>(instance, config::memetic::tabu::tenure,
                                                               config::memetic::tabu::neighborsConsideredInPerturbation,
                                                               config::memetic::tabu::maxGenerations,
                                                               config::memetic::tabu::maxStuck, rng);
            localSearch = [solver](const Solution& s, int timeMs) { return solver->run(s, timeMs); };
            break;
        }
        case LocalSearchMethod::NONE: {
            localSearch = [](const Solution& s, int timeMs) { return s; };
            break;
        }
        default: {
            throw std::invalid_argument("Unsupported local search method for memetic algorithm.");
        }
    }
}

void FlowShopMemetic::applyLocalSearch() {
    for (Solution& s : population) {
        s = localSearch(s, timeRemaining());
    }
}

vector<vector<int>> FlowShopMemetic::generateOrthogonalArray(const int size) {
    // Any column should have the same number of 1s and 0s
    // For every pair of columns, each combination of 2-bit strings should occur the same number of times
    // The selected combinations are uniformly distributed over the whole space of all the possible combinations
    vector<int> firstColumn = config::memetic::getFirstColumnOfOrthogonalArray(size + 1);
    vector orthogonalArray(size + 1, vector<int>(size)); // size + 1 rows and size columns
    for (int i = 0; i < size; i++) {
        orthogonalArray[i][0] = firstColumn[i];
    }

    // Fill the rest of the orthogonal array
    for (int j = 1; j < size; j++) {     // column j
        for (int i = 0; i < size; i++) { // row i
            int index = i - 1;
            if (index == -1) {
                index = size - 1;
            }
            orthogonalArray[i][j] = orthogonalArray[index][j - 1];
        }
    }

    // The last row is all 0s
    for (int i = 0; i < size + 1; i++) {
        orthogonalArray[i][size - 1] = 0;
    }

    return orthogonalArray;
}

vector<Solution> FlowShopMemetic::constructNewPopulation() {
    vector<Solution> newPopulation;
    while (newPopulation.size() < populationSize && !isTimeLimitReached()) {    // Check time limit
        // Select parents for crossover
        Solution parent1 = selectParent();
        Solution parent2 = selectParent();
        // Perform crossover
        Solution child = crossover(parent1, parent2);
        if (child < parent1 || child < parent2) {
            if (stuck > config::memetic::thresholdLocalSearch) {
                child = localSearch(child, timeRemaining());
            }
        }
        vector trio = {parent1, parent2, child};
        std::sort(trio.begin(), trio.end());
        // P1 and P2 are replaced by the best two of P1, P2, and child
        newPopulation.push_back(trio[0]);
        newPopulation.push_back(trio[1]);
    }

    return newPopulation;

}

vector<uint8_t> FlowShopMemetic::repair(const vector<uint8_t>& candidate, const Solution& reference) {
    std::set<uint8_t> seen;
    vector<uint8_t> repaired = candidate;
    vector<int> duplicatePositions;

    // Step 1: find duplicates
    for (int i = 0; i < repaired.size(); i++) {
        if (seen.count(repaired[i])) {      // .count() returns 1 if the element is already present, 0 otherwise
            duplicatePositions.push_back(i);
        } else {
            seen.insert(repaired[i]);
        }
    }

    // Step 2: find missing jobs
    vector<uint8_t> missing;
    for (uint8_t job : reference.getPermutation()) {
        if (!seen.count(job)) {
            missing.push_back(job);
        }
    }

    // Step 3: replace duplicates with missing jobs
    for (int i = 0; i < duplicatePositions.size(); i++) {
        repaired[duplicatePositions[i]] = missing[i];
    }

    return repaired;
}

vector<int> FlowShopMemetic::generateCutPoints(int nJobs) {
    std::set<int> cutSet;
    std::uniform_int_distribution<> dist(1, nJobs - 1); // avoid 0 and jobs to keep valid segments
    while (static_cast<int>(cutSet.size()) < numParentPieces - 1) {
        cutSet.insert(dist(rng));
    }
    std::vector<int> cutPoints = {0};
    cutPoints.insert(cutPoints.end(), cutSet.begin(), cutSet.end());
    cutPoints.push_back(nJobs);
    std::sort(cutPoints.begin(), cutPoints.end());

    return cutPoints;
}

vector<int> FlowShopMemetic::findBestLevels(const vector<Solution>& candidates, const vector<vector<int>>& orthogonalArray, int numFactors) {
    vector mainEffect(numFactors, vector<double>(2, 0));
    for (int i = 0; i < numFactors; i++) {
        const auto& row = orthogonalArray[i];
        double evaluation = 1.0 / static_cast<double>(candidates[i].getFitness());
        for (int j = 0; j < numFactors; j++) {
            int k = row[j];
            mainEffect[j][k] += evaluation;
        }
    }

    // Find the best level for each factor
    vector<int> bestLevels(numFactors);
    for (int j = 0; j < numFactors; ++j) {
        bestLevels[j] = (mainEffect[j][0] > mainEffect[j][1]) ? 0 : 1;
    }

    return bestLevels;
}

Solution FlowShopMemetic::crossover(const Solution &parent1, const Solution &parent2) {
    // Randomly choose numParentPieces–1 unique cut points to cut P1 and P2 into numParentPieces subsequences.
    vector<int> cutPoints = generateCutPoints(parent1.getNumberOfJobs());

    // Generate sampled childs for each line of the OA. The subsequence is taken from P1 or P2 depending on the value of the OA.
    // (0 = P1, 1 = P2)
    // Repair if necessary
    // Split parents into segments
    vector<vector<uint8_t>> segmentsP1, segmentsP2;
    for (int i = 0; i < numParentPieces; i++) {
        int start = cutPoints[i];
        int end = cutPoints[i + 1];
        segmentsP1.emplace_back(parent1.getPermutation().begin() + start, parent1.getPermutation().begin() + end);
        segmentsP2.emplace_back(parent2.getPermutation().begin() + start, parent2.getPermutation().begin() + end);
    }

    // Generate candidate children from the orthogonal array
    vector<Solution> candidates;
    for (const auto& row : crossoverOrthogonalArray) {
        if (isTimeLimitReached()) {     // For instances with a lot of jobs, checking the OA can take a lot of time
            return parent1;
        }
        vector<uint8_t> candidatePermutation;
        int startIndex = numParentPieces;       // index of the first segment where the parent changes
        int baseParent = row[0];        // 0 = P1, 1 = P2

        for (int j = 0; j < numParentPieces; ++j) {
            if (row[j] != baseParent && j < startIndex) {
                startIndex = j;             // index of the first segment where the parent changes
            }
            const auto& segment = (row[j] == 0) ? segmentsP1[j] : segmentsP2[j];
            candidatePermutation.insert(candidatePermutation.end(), segment.begin(), segment.end());
        }

        // Create a new solution based on parent1 or parent2 depending on the first segment (this avoids to recompute the fitness up to the first segment change)
        Solution candidate = baseParent == 0 ? parent1 : parent2;;
        candidatePermutation = repair(candidatePermutation, parent1); // Repair the candidate
        candidate.setPermutation(candidatePermutation);
        if (startIndex != numParentPieces) {
            candidate.evaluate(cutPoints[startIndex]);  // Evaluate the candidate only from the first point where the parent changes
            // Don't need to re-evaluate if startIndex == numParentPieces because the candidate then comes entirely from a single parent
        }
        candidates.emplace_back(candidate);
    }

    // Calculate the main effect  Fjk of factor j with level k, for j = [1, 2, .., N] and k = {0, 1}
    vector<int> bestLevels = findBestLevels(candidates, crossoverOrthogonalArray, numParentPieces);

    // Generate new child based on the best levels (Taguchi's method)
    vector<uint8_t> taguchiPermutation;
    for (int j = 0; j < numParentPieces; ++j) {
        const auto& segment = (bestLevels[j] == 0) ? segmentsP1[j] : segmentsP2[j];
        taguchiPermutation.insert(taguchiPermutation.end(), segment.begin(), segment.end());
    }

    Solution taguchiChild = parent1;
    taguchiPermutation = repair(taguchiPermutation, parent1);
    taguchiChild.setPermutation(taguchiPermutation);
    taguchiChild.evaluate(0);
    candidates.push_back(taguchiChild);

    return *std::min_element(candidates.begin(), candidates.end());
}

const Solution FlowShopMemetic::selectParent() {
    // Randomly select a parent from the population
    std::uniform_int_distribution dist(0, populationSize - 1);
    int index = dist(rng);
    return population[index];
}

Solution FlowShopMemetic::orthogonalArrayTest(const Solution &solution) {

    const int n = solution.getNumberOfJobs();
    std::uniform_int_distribution dist(0, n - 1);
    vector<std::pair<int, int>> mutationPositions;

    while (mutationPositions.size() < config::memetic::mutation::numberOfMutations) {
        int from = dist(rng);
        int to = dist(rng);
        if (from != to) {
            mutationPositions.emplace_back(from, to);
        }
    }

    std::vector<Solution> candidates;
    for (const auto& row: mutationOrthogonalArray) {
        Solution mutated = solution;
        int minFrom = n;
        for (int j = 0; j < mutationPositions.size(); j++) {
            if (row[j] == 1) {
                int from = mutationPositions[j].first;
                int to = mutationPositions[j].second;
                mutated = mutated.insert(from, to, 0, false);
                minFrom = std::min(minFrom, std::min(from, to));
            }
        }
        mutated.evaluate(minFrom); // Evaluate the solution only for the first mutation position
        candidates.push_back(mutated);
    }

    vector<int> bestLevels = findBestLevels(candidates, mutationOrthogonalArray, config::memetic::mutation::numberOfMutations);

    // Generate new child based on the best levels (Taguchi's method)
    Solution taguchiMutation = solution;
    int minFromTaguchi = n;
    for (int j = 0; j < config::memetic::mutation::numberOfMutations; ++j) {
        if (bestLevels[j] == 1) {
            int from = mutationPositions[j].first;
            int to = mutationPositions[j].second;
            taguchiMutation = taguchiMutation.insert(from, to, 0, false);
            minFromTaguchi = std::min(minFromTaguchi, std::min(from, to));
        }
    }
    taguchiMutation.evaluate(minFromTaguchi);
    candidates.push_back(taguchiMutation);

    return *std::min_element(candidates.begin(), candidates.end());
}

Solution FlowShopMemetic::mutate(Solution &solution) {
    Solution mutated = solution;
    bool isImproved = false;
    int generation = 0;
    int stuckMutation = 0;

    while (generation < config::memetic::mutation::maxGenerations && !isTimeLimitReached()) {
        Solution bestMutation = orthogonalArrayTest(solution);

        if (bestMutation < solution) {
            solution = bestMutation;
            stuckMutation = 0;
            if (bestMutation < mutated) {
                mutated = bestMutation;
                isImproved = true;
            }
        } else {
            stuckMutation++;
            if ((stuckMutation >= config::memetic::mutation::maxStuck) && (bestMutation.getFitness() < mutated.getFitness() * config::memetic::mutation::replaceRate)) {
                solution = bestMutation;
            }
        }
        generation++;
    }
    if (isImproved) {
        return mutated;
    } else {
        return solution; // Return the original solution if no improvement was found
    }
}

bool FlowShopMemetic::isTimeLimitReached() const {
    return chrono::duration_cast<chrono::milliseconds>(steady_clock::now() - startTime).count() >= maxExecutionTime;
}

int FlowShopMemetic::timeRemaining() const {
    return static_cast<int>(maxExecutionTime) -
           static_cast<int>(chrono::duration_cast<chrono::milliseconds>(steady_clock::now() - startTime).count());
}


Solution FlowShopMemetic::run(int timeLimit) {
    startTime = steady_clock::now();
    applyLocalSearch();
    std::sort(population.begin(), population.end());
    Solution best = population[0];
    while (!isTimeLimitReached()) {
        // Crossover
        vector<Solution> newPopulation = constructNewPopulation();
        std::sort(newPopulation.begin(), newPopulation.end());
        if (newPopulation[0] < best) {
            best = newPopulation[0];
            stuck = 0;
        } else {
            stuck++;
        }

        if (isTimeLimitReached()) {
            break; // Stop if the time limit is reached
        }

        // Mutation: apply to Ps * Pm individuals
        int numMutations = static_cast<int>(std::round(mutationRate * populationSize));
        std::uniform_int_distribution dist(0, populationSize - 1);
        for (int i = 0; i < numMutations && !isTimeLimitReached(); i++) {
            int idx = dist(rng);
            Solution mutated = mutate(newPopulation[idx]);
            newPopulation[idx] = mutated;
        }

        if (stuck > config::memetic::maxStuck) {
            return best; // Stop if no improvement is found for a while
        }

        population = newPopulation; // Update the population with the new individuals

    }

    std::sort(population.begin(), population.end());

    return population[0]; // Return the best solution found
}
