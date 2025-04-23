//
// Created by oscar on 15/03/2025.
//


#ifndef FLOWSHOPSLS_FLOWSHOPII_HPP
#define FLOWSHOPSLS_FLOWSHOPII_HPP
#include "flowShopSLS.hpp"

#include <memory>

using std::unique_ptr;

/**
 * @file flowShopII.hpp
 * @class FlowShopII
 * @brief The FlowShopII class is the class that implements the iterative improvement algorithm for the FlowShop problem.
 * It uses a neighbourhood structure and a pivoting rule to explore the solution space.
 * @field neighbourhoodIterator The neighbourhood iterator to use.
 * @see
 * <ul>
 * <li/> flowShopII.cpp in the src/core directory
 * <li/> flowShopSLS.hpp in the include/core directory
 * </ul>
 */
class FlowShopII : public FlowShopSLS {
    unique_ptr<NeighbourhoodIterator> neighbourhoodIterator; // The neighbourhood iterator to use

    /**
     * @brief The step function performs a single step of the iterative improvement algorithm. It uses the neighbourhood iterator to explore the solution space.
     * @return The best neighbour found in the neighbourhood or the first neighbour that improves the current solution depending on the pivoting rule.
     */
    Solution step() override;
public:

    /**
     * @brief The constructor of the FlowShopII class. It initializes the algorithm with the given instance, neighbourhood structure, pivoting rule, initialization method, and random number generator.
     * @param instance The instance of the problem.
     * @param neighbourhoodStructure The neighbourhood structure to use.
     * @param pivotRule The pivoting rule to use.
     * @param initMethod The initialization method to use.
     * @param rng The random number generator.
     */
    FlowShopII(const Instance &instance, NeighbourhoodStructure neighbourhoodStructure, PivotingRule pivotRule,
               InitializationMethod initMethod, std::mt19937 rng);

};


#endif //FLOWSHOPSLS_FLOWSHOPII_HPP
