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
    int stuck = 0; // Number of iterations without improvement

    double maxExecutionTime; // Maximum execution time for the algorithm, based on VND benchmark
    std::function<Solution(const Solution &)> localSearch; // Local search function to be used
    std::mt19937 rng; // Random number generator

    int numParentPieces; // Number of pieces into which the user wants to cut parent chromosomes P1 and P2 for recombination
    vector<vector<int>> orthogonalArray; // Orthogonal array to be used in the crossover operator


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
     * @brief The generateCutPoints function generates cut points for the crossover operator.
     * @param nJobs The parent solution to generate cut points from.
     * @return A vector of cut points.
     */
    vector<int> generateCutPoints(int nJobs);

    /**
     * @brief The repair function repairs a candidate solution by replacing duplicate jobs with missing jobs from the reference solution.
     * @param candidate The candidate solution to repair.
     * @param reference The reference solution to use for repairing the candidate. (for missing jobs)
     * @return The repaired solution.
     */
    static std::vector<uint8_t> repair(const std::vector<uint8_t>& candidate, const Solution& reference);

    /**
    * @brief The selectParent function selects a parent solution from the population using a selection method.
    * @return The selected parent solution.
    */
    const Solution selectParent();

    /**
     * @brief The constructNewPopulation function constructs a new population of solutions by applying crossover
     * @return A vector of new solutions.
     */
    vector<Solution> constructNewPopulation();

    /**
     * @brief The applyLocalSearch function applies the local search algorithm to the population.
     */
    void applyLocalSearch();

    /**
     * @brief The generateOrthogonalArray function generates an orthogonal array of size numCuts.
     */
    void generateOrthogonalArray();

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
