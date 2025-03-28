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


enum class InitializationMethod {
    RANDOM,
    SIMPLIFIED_RZ
};

enum class NeighbourhoodStructure {
    TRANSPOSE,
    EXCHANGE,
    INSERT
};

enum class PivotingRule {
    FIRST_IMPROVEMENT,
    BEST_IMPROVEMENT
};

class FlowShopII {
    Solution candidate;
    NeighbourhoodStructure neighbourhoodStructure;
    PivotingRule pivotingRule;

    public:
        FlowShopII(const Instance &instance, NeighbourhoodStructure neighborhoodStruct, PivotingRule pivotRule,
                   InitializationMethod initMethod, std::mt19937 rng);
        Solution run();
        Solution runBestImprovement();
        Solution runFirstImprovement();
        void getNeighbour(uint8_t i, uint8_t j);
};


#endif //FLOWSHOPSLS_FLOWSHOPII_HPP
