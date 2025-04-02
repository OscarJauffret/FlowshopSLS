//
// Created by oscar on 15/03/2025.
//

#include "../../include/core/flowShopII.hpp"
#include <iostream>

using std::cout;
using std::endl;

FlowShopII::FlowShopII(const Instance &instance, NeighbourhoodStructure neighbourhoodStructure, PivotingRule pivotRule,
                       InitializationMethod initMethod, std::mt19937 rng)
                       : FlowShopSLS(instance, pivotRule, initMethod, rng)
                       {
    switch(neighbourhoodStructure) {
        case NeighbourhoodStructure::TRANSPOSE:
            neighbourhoodIterator = std::make_unique<TransposeIterator>(candidate);
            break;
        case NeighbourhoodStructure::EXCHANGE:
            neighbourhoodIterator = std::make_unique<ExchangeIterator>(candidate);
            break;
        case NeighbourhoodStructure::INSERT:
            neighbourhoodIterator = std::make_unique<InsertIterator>(candidate);
            break;
    }
}

Solution FlowShopII::step() {
    Solution best = candidate;

    neighbourhoodIterator->setSolution(candidate);

    while(neighbourhoodIterator->hasNext()) {
        Solution neighbor = neighbourhoodIterator->next();   // Get the next neighbor. The fitness will be calculated here.

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

