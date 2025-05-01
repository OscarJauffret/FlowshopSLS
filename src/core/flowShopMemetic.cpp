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

using std::endl;
using std::cout;

FlowShopMemetic::FlowShopMemetic(const Instance& instance, int populationSize, LocalSearchMethod localSearchMethod,
                                 std::mt19937 rng)
    : populationSize(populationSize), numParentPieces(config::memetic::getNumCuts(instance.jobs)), rng(rng) {
    maxExecutionTime = MemeticTimeLimitProvider::getMemeticAllowedTime(instance.jobs);

    // Initialize the population with random solutions
    for (int i = 0; i < populationSize; ++i) {
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
    orthogonalArray.resize(numParentPieces + 1, vector<int>(numParentPieces));
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

Solution FlowShopMemetic::crossover(const Solution &parent1, const Solution &parent2) {
    // Randomly choose numParentPieces–1 unique cut points to cut P1 and P2 into numParentPieces subsequences.
    int jobs = parent1.getNumberOfJobs();
    std::set<int> cutSet;
    std::uniform_int_distribution<> dist(1, jobs - 1); // avoid 0 and jobs to keep valid segments
    while (static_cast<int>(cutSet.size()) < numParentPieces - 1) {
        cutSet.insert(dist(rng));
    }
    std::vector<int> cutPoints = {0};
    cutPoints.insert(cutPoints.end(), cutSet.begin(), cutSet.end());
    cutPoints.push_back(jobs);
    std::sort(cutPoints.begin(), cutPoints.end());



    return parent1; // Placeholder for crossover logic
}

const Solution FlowShopMemetic::selectParent() {
    // Randomly select a parent from the population
    std::uniform_int_distribution dist(0, populationSize - 1);
    int index = dist(rng);
    return population[index];
}

Solution FlowShopMemetic::run() {
    auto start = std::chrono::steady_clock::now();
    applyLocalSearch();
    std::sort(population.begin(), population.end());
    while (std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start).count() < maxExecutionTime) {
        // Select parents for crossover
        Solution parent1 = selectParent();
        Solution parent2 = selectParent();
        // Perform crossover
        Solution child = crossover(parent1, parent2);
        return population[0];
    }

    return population[0]; // Return the best solution found
}