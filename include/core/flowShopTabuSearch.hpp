//
// Created by oscar on 06/05/2025.
//

#ifndef PFSP_FLOWSHOPTABUSEARCH_HPP
#define PFSP_FLOWSHOPTABUSEARCH_HPP

#include "flowShopSolver.hpp"
#include "../neighbourhoods/insertIterator.hpp"
#include <deque>
#include <utility>
#include <random>
#include <chrono>

using std::pair;
using std::deque;
using std::chrono::steady_clock;

/**
 * @class FlowShopTabuSearch
 * @brief The FlowShopTabuSearch class implements the Tabu Search algorithm for the Flow Shop Scheduling Problem.
 * It extends the FlowShopSolver class and provides a specific implementation of the run method.
 * @field candidate The current candidate solution.
 * @field tabuTenure The tabuTenure of the tabu list.
 * @field maxGenerations The maximum number of generations to run the algorithm.
 * @field maxStuck The maximum number of generations without improvement before stopping the algorithm.
 * @field allowedTime The maximum execution time for the algorithm, based on VND benchmark.
 * @field tabuList The list of tabu moves.
 * @field insertIterator The insert iterator to use for the neighborhood search.
 * @field rng The random number generator to use for the algorithm.
 */
class FlowShopTabuSearch: public FlowShopSolver {

    Solution candidate;

    int tabuTenure;
    int maxGenerations;
    int maxStuck;

    int allowedTime;

    deque<pair<uint8_t , uint8_t>> tabuList;
    InsertIterator insertIterator;
    std::mt19937& rng;

    /**
     * @brief The isTabu function checks if a move is tabu. A move is tabu if it is in the tabu list.
     * @param from The index of the job to insert.
     * @param to The index where to insert the job.
     * @return True if the move is tabu, false otherwise.
     */
    [[nodiscard]] bool isTabu(int from, int to);

    /**
     * @brief The addToTabuList function adds a move to the tabu list. If the list is full, it removes the oldest move.
     * @param fromToPair The move to add to the tabu list.
     */
    void addToTabuList(int from, int to);

    /**
     * @brief The shouldStop function checks if the algorithm should stop.
     * @param generations The current number of generations.
     * @param start The start time of the algorithm.
     * @param timeLimit The time limit for the algorithm in milliseconds. If -1, the algorithm runs until no improvement is found.
     * @return True if the algorithm should stop, false otherwise.
     */
    [[nodiscard]] bool shouldStop(int generations, steady_clock::time_point start, int timeLimit) const;

public:
    /**
     * @brief The constructor of the FlowShopTabuSearch class. It initializes the candidate solution, tabuTenure, alpha, maxGenerations, maxStuck and rng.
     * @param instance The instance of the problem to solve.
     * @param tabuTenure The tabuTenure of the tabu list.
     * @param alpha The parameter that controls the extent of the neighborhood search. The neighborhood search is insertion neighborhood search.
     * For example, if alpha = 3, each job can be inserted 3 positions before or after its current position. (This is from the paper of Lin-Yu Tseng and Ya-Tai Lin)
     * @param maxGenerations The maximum number of generations to run the algorithm.
     * @param maxStuck The maximum number of generations without improvement before performing a perturbation.
     * @param rng The random number generator to use for the algorithm.
     */
    FlowShopTabuSearch(const Instance& instance, int tabuTenure, int alpha, int maxGenerations, int maxStuck, std::mt19937& rng);

    /**
     * @brief The run function runs the Tabu Search algorithm. It iteratively improves the candidate solution by exploring the neighborhood and applying tabu search.
     * @param timeLimit The time limit for the algorithm in milliseconds. If -1, the algorithm runs until no improvement is found.
     * @return The best solution found during the search.
     */
    Solution run(int timeLimit) override;

    /**
     * @brief The run function runs the Tabu Search algorithm with a given initial solution. It iteratively improves the candidate solution by exploring the neighborhood and applying tabu search.
     * @param initialSolution The initial solution to start the search from.
     * @param timeLimit The time limit for the algorithm in milliseconds. If -1, the algorithm runs until no improvement is found.
     * @return The best solution found during the search.
     */
    Solution run(const Solution& initialSolution, int timeLimit) {
        candidate = initialSolution;
        return run(timeLimit);
    }
};


#endif //PFSP_FLOWSHOPTABUSEARCH_HPP
