//
// Created by oscar on 15/03/2025.
//

#include "../../include/core/flowShopII.hpp"
#include <iostream>

using std::cout;
using std::endl;

FlowShopII::FlowShopII(const Instance &instance, NeighbourhoodStructure neighborhoodStruct, PivotingRule pivotRule,
                       InitializationMethod initMethod, std::mt19937 rng)
                       : FlowShopSLS(instance, pivotRule, initMethod, rng)
                       {
    switch(neighborhoodStruct) {
        case NeighbourhoodStructure::TRANSPOSE:
            neighborhoodIterator = std::make_unique<TransposeIterator>(candidate);
            break;
        case NeighbourhoodStructure::EXCHANGE:
            neighborhoodIterator = std::make_unique<ExchangeIterator>(candidate);
            break;
        case NeighbourhoodStructure::INSERT:
            neighborhoodIterator = std::make_unique<InsertIterator>(candidate);
            break;
    }
}

Solution FlowShopII::step() {
    Solution best = candidate;

    neighborhoodIterator->setSolution(candidate);

    while(neighborhoodIterator->hasNext()) {
        Solution neighbor = neighborhoodIterator->next();   // Get the next neighbor. The fitness will be calculated here.

        if (neighbor.getFitness() < best.getFitness()) {
            if (pivotingRule == PivotingRule::FIRST_IMPROVEMENT) {
                return neighbor;
            } else {
                best = neighbor;
            }
        }
    }
    return best;
}

