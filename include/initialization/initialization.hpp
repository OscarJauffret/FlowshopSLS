//
// Created by oscar on 09/03/2025.
//
#ifndef FLOWSHOPSLS_INITIALIZATION_HPP
#define FLOWSHOPSLS_INITIALIZATION_HPP

#include "../core/solution.hpp"
#include <random>
#include <algorithm>
#include <numeric>

/**
 * @file initialization.hpp
 * @namespace initialization
 * @brief The initialization namespace contains the functions to initialize the solution.
 * <br> The available initialization functions are:
 * <ul>
 * <li>Random initialization</li>
 * <li>Simplified RZ heuristic</li>
 * </ul>
 *
 * @see initialization.cpp
 */
namespace initialization {

    /**
     * @brief The random function initializes the solution with a random permutation of the jobs.
     * @param instance The instance of the problem.
     * @param rng The random number generator.
     * @return The solution with a random permutation of the jobs.
     */
    Solution random(const Instance& instance, std::mt19937& rng);

    /**
     * @brief The simplifiedRZ function initializes the solution with the simplified RZ heuristic.
     * @param instance The instance of the problem.
     * @param rng The random number generator.
     * @return The solution with the simplified RZ heuristic.
     */
    Solution simplifiedRZ(const Instance &instance, std::mt19937 &rng);
}

#endif //FLOWSHOPSLS_INITIALIZATION_HPP