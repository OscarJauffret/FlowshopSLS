//
// Created by oscar on 06/05/2025.
//

#ifndef PFSP_FLOWSHOPTABUSEARCH_HPP
#define PFSP_FLOWSHOPTABUSEARCH_HPP

#include "flowShopSolver.hpp"
#include <deque>
#include <utility>
#include <random>

using std::pair;
using std::deque;

/**
 * @class FlowShopTabuSearch
 * @brief The FlowShopTabuSearch class implements the Tabu Search algorithm for the Flow Shop Scheduling Problem.
 * It extends the FlowShopSolver class and provides a specific implementation of the run method.
 * @field candidate The current candidate solution.
 * @field tenure The tenure of the tabu list.
 * @field tabuList The list of tabu moves.
 * @field alpha The parameter that controls the extent of the neighborhood search. The neighborhood search is insertion neighborhood search.
 * For example, if alpha = 3, each job can be inserted 3 positions before or after its current position. (This is from the paper of Lin-Yu Tseng and Ya-Tai Lin)
 * @field maxGenerations The maximum number of generations to run the algorithm.
 * @field maxStuck The maximum number of generations without improvement before stopping the algorithm.
 */
class FlowShopTabuSearch: public FlowShopSolver {

    Solution candidate;
    int tenure;
    deque<pair<int, int>> tabuList;
    int alpha;
    int maxGenerations;
    int maxStuck;

public:
    FlowShopTabuSearch(const Instance& instance, int tabuTenure, int alpha, int maxGenerations, int maxStuck, std::mt19937& rng);

    Solution run() override;

    Solution run(const Solution& initialSolution) {
        candidate = initialSolution;
        return run();
    }
};


#endif //PFSP_FLOWSHOPTABUSEARCH_HPP
