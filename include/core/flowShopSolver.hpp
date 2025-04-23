//
// Created by Oscar Jauffret on 23/04/2025.
//

#ifndef FLOWSHOPSOLVER_HPP
#define FLOWSHOPSOLVER_HPP

#include "solution.hpp"


class FlowShopSolver {
public:
    virtual Solution run() = 0;
    virtual ~FlowShopSolver() = default;
};

#endif //FLOWSHOPSOLVER_HPP
