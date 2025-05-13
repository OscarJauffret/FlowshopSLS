//
// Created by Oscar Jauffret on 23/04/2025.
//

#ifndef FLOWSHOPSOLVER_HPP
#define FLOWSHOPSOLVER_HPP

#include "solution.hpp"

/**
 * @file flowShopSolver.hpp
 * @class FlowShopSolver
 * @brief The FlowShopSolver class is an abstract class that represents a solver for the Flow Shop Scheduling Problem.
 */
class FlowShopSolver {
public:
    /**
     * @brief The run function runs the algorithm.
     * @param timeLimit The time limit for the algorithm in milliseconds. If -1, the algorithm runs until no improvement is found.
     * @return The best solution found by the algorithm.
     */
    virtual Solution run(int timeLimit) = 0;

    /**
     * @brief Default destructor for the FlowShopSolver class. It is used for inheritance
     */
    virtual ~FlowShopSolver() = default;
};

#endif //FLOWSHOPSOLVER_HPP
