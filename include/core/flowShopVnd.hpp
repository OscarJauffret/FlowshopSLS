//
// Created by oscar on 01/04/2025.
//

#ifndef PFSP_II_FLOWSHOPVND_HPP
#define PFSP_II_FLOWSHOPVND_HPP

#include "flowShopSLS.hpp"

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

/**
 * @file flowShopVnd.hpp
 * @class FlowShopVND
 * @brief The FlowShopVND class represents the VND algorithm for the Flow Shop Scheduling Problem.
 * For this algorithm, two neighbourhood orders are available:
 * <ul>
 * <li/> Transpose-Exchange-Insert
 * <li/> Transpose-Insert-Exchange
 * </ul>
 * The initialization method is the simplified RZ heuristic.
 *
 * @field neighbourhoodIterators The neighbourhood iterators to use.
 * @see
 * <ul>
 * <li/> flowShopVnd.cpp in the src/core directory
 * <li/> flowShopSLS.hpp in the include/core directory
 * </ul>
 */
class FlowShopVND : public FlowShopSLS {
    vector<unique_ptr<NeighbourhoodIterator>> neighbourhoodIterators; // The neighbourhood iterators to use

    /**
     * @brief The step function performs a single step of the VND algorithm. It uses the neighbourhood iterator to explore the solution space.
     * @return The first neighbor that improves the current solution.
     */
    Solution step() override;
public:

    /**
     * @brief The constructor of the FlowShopVND class. It initializes the algorithm with the given instance, and neighbourhood order.
     * @param instance The instance of the problem.
     * @param neighbourhoodOrder The order in which to go through the neighbourhoods.
     * @param rng The random number generator.
     */
    FlowShopVND(const Instance &instance, VNDStrategy neighbourhoodOrder, std::mt19937 rng);

};


#endif //PFSP_II_FLOWSHOPVND_HPP
