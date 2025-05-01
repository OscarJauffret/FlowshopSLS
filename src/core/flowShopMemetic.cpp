//
// Created by Oscar Jauffret on 21/04/2025.
//

#include "../../include/core/flowShopMemetic.hpp"
#include "../../include/initialization/initialization.hpp"
#include "../../include/utils/memeticTimeLimitProvider.hpp"
#include "../../include/core/flowShopII.hpp"
#include "../../include/core/flowShopVnd.hpp"
#include "../../include/config/flowShopConfig.hpp"
#include <iostream>
#include <set>

#include "../config.hpp"

namespace chrono = std::chrono;

using std::endl;
using std::cout;
using chrono::steady_clock;

FlowShopMemetic::FlowShopMemetic(const Instance& instance, int populationSize, LocalSearchMethod localSearchMethod,
                                 std::mt19937 rng)
    : populationSize(populationSize), numParentPieces(config::memetic::getNumCuts(instance.jobs)), rng(rng) {
    maxExecutionTime = MemeticTimeLimitProvider::getMemeticAllowedTime(instance.jobs);

    // Initialize the population with random solutions
    for (int i = 0; i < populationSize; i++) {
        // Generate a random permutation of jobs
        Solution solution = initialization::random(instance, rng);
        population.push_back(solution);
    }

    initializeLocalSearchFunction(instance, localSearchMethod, rng);
    generateOrthogonalArray();
}

void FlowShopMemetic::initializeLocalSearchFunction(const Instance& instance, LocalSearchMethod localSearchMethod, std::mt19937 rng) {
    switch (localSearchMethod) {
        case LocalSearchMethod::II: {
            auto solver = std::make_shared<FlowShopII>(instance, NeighbourhoodStructure::INSERT,
                                                       PivotingRule::BEST_IMPROVEMENT, InitializationMethod::RANDOM,
                                                       rng);
            localSearch = [solver](const Solution& s) { return solver->run(s); };
            break;
        }
        case LocalSearchMethod::VND: {
            auto solver = std::make_shared<FlowShopVND>(instance, VNDStrategy::TEI, rng);
            localSearch = [solver](const Solution& s) { return solver->run(s); };
            break;
        }
        case LocalSearchMethod::NONE: {
            localSearch = [](const Solution& s) { return s; };
            break;
        }
        default: {
            throw std::invalid_argument("Unsupported local search method for memetic algorithm.");
        }
    }
}

void FlowShopMemetic::applyLocalSearch() {
    for (Solution& s : population) {
        s = localSearch(s);
    }
}

void FlowShopMemetic::generateOrthogonalArray() {
    // Any column should have the same number of 1s and 0s
    // For every pair of columns, each combination of 2-bit strings should occur the same number of times
    // The selected combinations are uniformly distributed over the whole space of all the possible combinations
    vector<int> firstColumn = config::memetic::getFirstColumnOfOrthogonalArray(numParentPieces + 1);
    orthogonalArray.resize(numParentPieces + 1, vector<int>(numParentPieces));  // numParentPieces + 1 rows and numParentPieces columns
    for (int i = 0; i < numParentPieces; i++) {
        orthogonalArray[i][0] = firstColumn[i];
    }

    // Fill the rest of the orthogonal array
    for (int j = 1; j < numParentPieces; j++) {     // column j
        for (int i = 0; i < numParentPieces; i++) { // row i
            int index = i - 1;
            if (index == -1) {
                index = numParentPieces - 1;
            }
            orthogonalArray[i][j] = orthogonalArray[index][j - 1];
        }
    }

    // The last row is all 0s
    for (int i = 0; i < numParentPieces + 1; i++) {
        orthogonalArray[i][numParentPieces - 1] = 0;
    }
}


Solution FlowShopMemetic::mutate(const Solution &solution) {
    return solution; // Placeholder for mutation logic
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


Solution FlowShopMemetic::crossover(const Solution &parent1, const Solution &parent2) {
    // Randomly choose numParentPieces–1 unique cut points to cut P1 and P2 into numParentPieces subsequences.
    vector<int> cutPoints = generateCutPoints(parent1.getNumberOfJobs());

    // Generate sampled childs for each line of the OA. The subsequence is taken from P1 or P2 depending on the value of the OA.
    // (0 = P1, 1 = P2)
    // Repair if necessary
    // Split parents into segments
    std::vector<std::vector<uint8_t>> segmentsP1, segmentsP2;
    for (int i = 0; i < numParentPieces; i++) {
        int start = cutPoints[i];
        int end = cutPoints[i + 1];
        segmentsP1.emplace_back(parent1.getPermutation().begin() + start, parent1.getPermutation().begin() + end);
        segmentsP2.emplace_back(parent2.getPermutation().begin() + start, parent2.getPermutation().begin() + end);
    }

    // Generate candidate children from the orthogonal array
    std::vector<Solution> candidates;
    for (const auto& row : orthogonalArray) {
        std::vector<uint8_t> candidatePermutation;

        for (int j = 0; j < numParentPieces; ++j) {
            const auto& segment = (row[j] == 0) ? segmentsP1[j] : segmentsP2[j];
            candidatePermutation.insert(candidatePermutation.end(), segment.begin(), segment.end());
        }

        Solution candidate = parent1; // Create a new solution based on parent1
        candidatePermutation = repair(candidatePermutation, parent1); // Repair the candidate
        candidate.setPermutation(candidatePermutation);
        candidate.evaluate(0);
        candidates.emplace_back(candidate);
    }

    // Calculate the main effect  Fjk of factor j with level k, for j = [1, 2, .., N] and k = {0, 1}
    vector mainEffect(numParentPieces, vector<double>(2, 0));
    for (int i = 0; i < numParentPieces; i++) {
        const auto& row = orthogonalArray[i];
        double evaluation = 1.0 / static_cast<double>(candidates[i].getFitness());
        for (int j = 0; j < numParentPieces; j++) {
            int k = row[j];
            mainEffect[j][k] += evaluation;
        }
    }

    // Find the best level for each factor
    vector<int> bestLevel(numParentPieces);
    for (int j = 0; j < numParentPieces; ++j) {
        bestLevel[j] = (mainEffect[j][0] > mainEffect[j][1]) ? 0 : 1;
    }

    // Generate new child based on the best levels (Taguchi's method)
    vector<uint8_t> taguchiPermutation;
    for (int j = 0; j < numParentPieces; ++j) {
        const auto& segment = (bestLevel[j] == 0) ? segmentsP1[j] : segmentsP2[j];
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

vector<Solution> FlowShopMemetic::constructNewPopulation() {
    vector<Solution> newPopulation;
    while (newPopulation.size() < populationSize) {
        // Select parents for crossover
        Solution parent1 = selectParent();
        Solution parent2 = selectParent();
        // Perform crossover
        Solution child = crossover(parent1, parent2);
        if (child < parent1 || child < parent2) {
            if (stuck > config::memetic::thresholdLocalSearch) {
                child = localSearch(child);
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

Solution FlowShopMemetic::run() {
    auto start = steady_clock::now();
    applyLocalSearch();
    std::sort(population.begin(), population.end());
    best = population[0];
    while (chrono::duration_cast<chrono::milliseconds>(steady_clock::now() - start).count() < maxExecutionTime) {
        vector<Solution> newPopulation = constructNewPopulation();

        std::sort(newPopulation.begin(), newPopulation.end());
        if (newPopulation[0] < best) {
            best = newPopulation[0];
            stuck = 0;
        } else {
            stuck++;
        }


    }

    return population[0]; // Return the best solution found
}
