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

using std::endl;
using std::cout;

FlowShopMemetic::FlowShopMemetic(const Instance& instance, int populationSize, LocalSearchMethod localSearchMethod,
                                 std::mt19937 rng)
    : populationSize(populationSize) {
    maxExecutionTime = MemeticTimeLimitProvider::getMemeticAllowedTime(instance.jobs);

    // Initialize the population with random solutions
    for (int i = 0; i < populationSize; ++i) {
        // Generate a random permutation of jobs
        Solution solution = initialization::random(instance, rng);
        population.push_back(solution);
    }

    initializeLocalSearchFunction(instance, localSearchMethod, rng);
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

Solution FlowShopMemetic::mutate(const Solution &solution) {
    return solution; // Placeholder for mutation logic
}

Solution FlowShopMemetic::crossover(const Solution &parent1, const Solution &parent2) {
    return parent1; // Placeholder for crossover logic
}

const Solution FlowShopMemetic::selectParent() {
    return population[0]; // Placeholder for parent selection logic
}

Solution FlowShopMemetic::run() {
    auto start = std::chrono::steady_clock::now();
    applyLocalSearch();

    return population[0]; // Return the best solution found
}