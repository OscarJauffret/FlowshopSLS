//
// Created by oscar on 15/03/2025.
//


#ifndef FLOWSHOPSLS_FLOWSHOPII_HPP
#define FLOWSHOPSLS_FLOWSHOPII_HPP
#include "solution.hpp"
#include "../initialization/initialization.hpp"
#include "../neighborhoods/neighborhoodIterator.hpp"
#include "../neighborhoods/transposeIterator.hpp"
#include "../neighborhoods/exchangeIterator.hpp"
#include "../neighborhoods/insertIterator.hpp"
#include "../utils/flowShopConfig.hpp"


/**
 * @file flowShopII.hpp
 * @class FlowShopII
 * @brief The FlowShopII class is the class that implements the iterative improvement algorithm for the FlowShop problem.
 * It uses a neighborhood structure and a pivoting rule to explore the solution space.
 * @field candidate The current candidate solution.
 * @field pivotingRule The pivoting rule to use.
 * @field neighborhoodIterator The neighborhood iterator to use.
 * @see flowShopII.cpp in the src/core directory
 */
class FlowShopII {
    Solution candidate;                                         // The current candidate solution
    PivotingRule pivotingRule;                                  // The pivoting rule to use
    std::unique_ptr<NeighborhoodIterator> neighborhoodIterator; // The neighborhood iterator to use

private:
    /**
     * @brief The step function performs a single step of the iterative improvement algorithm. It uses the neighborhood iterator to explore the solution space.
     * @return The best neighbor found in the neighborhood or the first neighbor that improves the current solution depending on the pivoting rule.
     */
    Solution step();
public:

    /**
     * @brief The constructor of the FlowShopII class. It initializes the algorithm with the given instance, neighborhood structure, pivoting rule, initialization method, and random number generator.
     * @param instance The instance of the problem.
     * @param neighborhoodStruct The neighborhood structure to use.
     * @param pivotRule The pivoting rule to use.
     * @param initMethod The initialization method to use.
     * @param rng The random number generator.
     */
    FlowShopII(const Instance &instance, NeighbourhoodStructure neighborhoodStruct, PivotingRule pivotRule,
               InitializationMethod initMethod, std::mt19937 rng);

    /**
     * @brief The run function runs the iterative improvement algorithm until no improvement is found.
     * @return The best solution found by the algorithm.
     */
    Solution run();
};


#endif //FLOWSHOPSLS_FLOWSHOPII_HPP
