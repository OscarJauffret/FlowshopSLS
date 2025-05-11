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
#include <chrono>

namespace chrono = std::chrono;

using std::vector;
using chrono::steady_clock;

class FlowShopMemetic: public FlowShopSolver {
    vector<Solution> population; // Population of solutions
    int populationSize; // Size of the population
    float mutationRate; // Mutation rate
    int stuck = 0; // Number of iterations without improvement

    double maxExecutionTime; // Maximum execution time for the algorithm, based on VND benchmark
    steady_clock::time_point startTime;
    std::function<Solution(const Solution &, int timeMs)> localSearch; // Local search function to be used
    std::mt19937 rng; // Random number generator

    int numParentPieces; // Number of pieces into which the user wants to cut parent chromosomes P1 and P2 for recombination
    vector<vector<int>> crossoverOrthogonalArray; // Orthogonal array to be used in the crossover operator
    vector<vector<int>> mutationOrthogonalArray;


    /**
    * @brief The orthogonalArrayTest function finds the best combination of mutations among randomly selected
    * This is the implementation of the OATest function from the paper of Lin-Yu Tseng and Ya-Tai Lin.
    * @param solution The solution to orthogonalArrayTest.
    * @return The mutated solution.
    */
    Solution orthogonalArrayTest(const Solution &solution);

    /**
    * @brief The mutate function mutates a solution by applying a mutation operator.
    * @param solution The solution to orthogonalArrayTest.
    * @return The mutated solution.
    */
    Solution mutate(Solution &solution);

    /**
    * @brief The crossover function combines two parent solutions to create a new solution.
    * The implementations is the one used in the paper of Lin-Yu Tseng and Ya-Tai Lin.
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
     * @brief The findBestLevels function finds the best levels for the orthogonal array based on the candidates evaluationsa
     * @param candidates The candidate solutions to evaluate.
     * @param orthogonalArray The orthogonal array to use for the evaluation.
     * @param numFactors The number of factors in the orthogonal array.
     * @return A vector of best levels for each factor.
     */
    static vector<int> findBestLevels(const std::vector<Solution>& candidates, const vector<vector<int>>& orthogonalArray, int numFactors);

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
    static vector<vector<int>> generateOrthogonalArray(int size);

    /**
     * @brief The initializeLocalSearchFunction function initializes the local search function based on
     * the provided local search method.
     * @param instance
     * @param localSearchMethod The local search method to be used.
     */
    void initializeLocalSearchFunction(const Instance &instance, LocalSearchMethod localSearchMethod);

    /**
     * @brief The isTimeLimitReached function checks if the time limit for the algorithm has been reached.
     * @return True if the time limit is reached, false otherwise.
     */
    [[nodiscard]] bool isTimeLimitReached() const;

    /**
     * @brief The timeRemaining function calculates the remaining time for the algorithm.
     * @return The remaining time in milliseconds.
     */
    [[nodiscard]] int timeRemaining() const;

public:
    /**
    * @brief The constructor of the FlowShopMemetic class. It initializes the population with random solutions.
    * @param instance The instance of the problem.
    * @param populationSize The size of the population.
    * @param mutationRate The mutation rate to use.
    * @param localSearch The local search method to use.
    * @param rng The random number generator.
    */
    FlowShopMemetic(const Instance &instance, int populationSize, float mutationRate, LocalSearchMethod localSearch, std::mt19937 rng);

    /**
    * @brief The run function runs the memetic algorithm until convergence or a maximum number of iterations is reached.
    * @return The best solution found by the algorithm.
    */
    Solution run(int timeLimit) override;
};



#endif //FLOWSHOPMEMETIC_HPP
