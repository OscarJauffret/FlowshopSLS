//
// Created by oscar on 15/03/2025.
//

#include "../../include/core/flowShopII.hpp"
#include "../../include/neighborhoods/transposeIterator.hpp"
#include "../../include/neighborhoods/exchangeIterator.hpp"
#include "../../include/neighborhoods/insertIterator.hpp"

#include <iostream>

using std::cout;
using std::endl;

FlowShopII::FlowShopII(const Instance &instance, NeighbourhoodStructure neighborhoodStruct, PivotingRule pivotRule,
                       InitializationMethod initMethod, std::mt19937 rng)
                       : pivotingRule(pivotRule),
                       candidate(initMethod == InitializationMethod::RANDOM
                                    ? initialization::random(instance, rng)
                                    : initialization::simplifiedRZ(instance))
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

Solution FlowShopII::run() {
    Solution prev(candidate);
    do {
        cout << "Candidate: " << candidate << endl;
        prev = candidate;
        candidate = step();
    } while(candidate.getFitness() < prev.getFitness());

    return candidate;
}

Solution FlowShopII::step() {
    Solution best = candidate;

    neighborhoodIterator->setSolution(candidate);

    while(neighborhoodIterator->hasNext()) {
        Solution neighbor = neighborhoodIterator->next();

        if (neighbor.evaluate() < best.getFitness()) {
            if (pivotingRule == PivotingRule::FIRST_IMPROVEMENT) {
                return neighbor;
            } else {
                best = neighbor;
            }
        }
    }

    return best;

}

