//
// Created by Oscar Jauffret on 23/04/2025.
//

#ifndef FLOWSHOPSOLVER_HPP
#define FLOWSHOPSOLVER_HPP

#include "solution.hpp"


class FlowShopSolver {
public:
    /**
     * @brief The run function runs the algorithm.
     * @return The best solution found by the algorithm.
     */
    virtual Solution run() = 0;

    /**
     * @brief Default destructor for the FlowShopSolver class. It is used for inheritance
     */
    virtual ~FlowShopSolver() = default;
};

#endif //FLOWSHOPSOLVER_HPP
