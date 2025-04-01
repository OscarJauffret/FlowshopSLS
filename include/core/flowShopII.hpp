//
// Created by oscar on 15/03/2025.
//


#ifndef FLOWSHOPSLS_FLOWSHOPII_HPP
#define FLOWSHOPSLS_FLOWSHOPII_HPP
#include "flowShopSLS.hpp"

using std::unique_ptr;

/**
 * @file flowShopII.hpp
 * @class FlowShopII
 * @brief The FlowShopII class is the class that implements the iterative improvement algorithm for the FlowShop problem.
 * It uses a neighborhood structure and a pivoting rule to explore the solution space.
 * @field neighborhoodIterator The neighborhood iterator to use.
 * @see
 * <ul>
 * <li/> flowShopII.cpp in the src/core directory
 * <li/> flowShopSLS.hpp in the include/core directory
 * </ul>
 */
class FlowShopII : public FlowShopSLS {
private:
    unique_ptr<NeighborhoodIterator> neighborhoodIterator; // The neighborhood iterator to use

    /**
     * @brief The step function performs a single step of the iterative improvement algorithm. It uses the neighborhood iterator to explore the solution space.
     * @return The best neighbor found in the neighborhood or the first neighbor that improves the current solution depending on the pivoting rule.
     */
    Solution step() override;
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

};


#endif //FLOWSHOPSLS_FLOWSHOPII_HPP
