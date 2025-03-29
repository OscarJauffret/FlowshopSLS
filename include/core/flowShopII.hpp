//
// Created by oscar on 15/03/2025.
//

/**
 * @file flowShopII.hpp
 * @brief The FlowShopII class is the class that implements the iterative improvement algorithm for the FlowShop problem.
 *
 * @see FlowShopII.cpp
 */

#ifndef FLOWSHOPSLS_FLOWSHOPII_HPP
#define FLOWSHOPSLS_FLOWSHOPII_HPP
#include "solution.hpp"
#include "../initialization/initialization.hpp"
#include "../neighborhoods/neighborhoodIterator.hpp"
#include "../neighborhoods/transposeIterator.hpp"
#include "../neighborhoods/exchangeIterator.hpp"
#include "../neighborhoods/insertIterator.hpp"
#include "../utils/flowShopConfig.hpp"


class FlowShopII {
    Solution candidate;
    PivotingRule pivotingRule;
    std::unique_ptr<NeighborhoodIterator> neighborhoodIterator;

private:
    Solution step();
public:
    FlowShopII(const Instance &instance, NeighbourhoodStructure neighborhoodStruct, PivotingRule pivotRule,
               InitializationMethod initMethod, std::mt19937 rng);
    Solution run();
};


#endif //FLOWSHOPSLS_FLOWSHOPII_HPP
