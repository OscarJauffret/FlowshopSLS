//
// Created by Oscar Jauffret on 21/04/2025.
//

#ifndef FLOWSHOPMEMETIC_HPP
#define FLOWSHOPMEMETIC_HPP

#include "../config/flowShopConfigMemetic.hpp"
#include "solution.hpp"
#include "flowShopSolver.hpp"
#include <vector>
#include <random>
#include <functional>

using std::vector;

class FlowShopMemetic: public FlowShopSolver {
    vector<Solution> population; // Population of solutions
    int populationSize; // Size of the population
    double maxExecutionTime; // Maximum execution time for the algorithm, based on VND benchmark
    std::function<Solution(const Solution &)> localSearch; // Local search function to be used


    /**
    * @brief The mutate function applies a mutation operator to a solution.
    * @param solution The solution to mutate.
    * @return The mutated solution.
    */
    Solution mutate(const Solution &solution);

    /**
    * @brief The crossover function combines two parent solutions to create a new solution.
    * @param parent1 The first parent solution.
    * @param parent2 The second parent solution.
    * @return The new solution created by combining the two parents.
    */
    Solution crossover(const Solution &parent1, const Solution &parent2);

    /**
    * @brief The selectParent function selects a parent solution from the population using a selection method.
    * @return The selected parent solution.
    */
    const Solution selectParent();

    /**
     * @brief The initializeLocalSearchFunction function initializes the local search function based on
     * the provided local search method.
     * @param instance
     * @param localSearchMethod The local search method to be used.
     * @param rng The random number generator to be used.
     */
    void initializeLocalSearchFunction(const Instance& instance, LocalSearchMethod localSearchMethod, std::mt19937 rng);

public:
    /**
    * @brief The constructor of the FlowShopMemetic class. It initializes the population with random solutions.
    * @param instance The instance of the problem.
    * @param populationSize The size of the population.
    * @param localSearch The local search method to be used.
    * @param rng The random number generator.
    */
    FlowShopMemetic(const Instance &instance, int populationSize, LocalSearchMethod localSearch, std::mt19937 rng);

    /**
    * @brief The run function runs the memetic algorithm until convergence or a maximum number of iterations is reached.
    * @return The best solution found by the algorithm.
    */
    Solution run() override;
};



#endif //FLOWSHOPMEMETIC_HPP
