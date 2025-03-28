//
// Created by oscar on 15/03/2025.
//

#include "../../include/core/flowShopII.hpp"

FlowShopII::FlowShopII(const Instance &instance, NeighbourhoodStructure neighborhoodStruct, PivotingRule pivotRule,
                       InitializationMethod initMethod, std::mt19937 rng)
                       : neighbourhoodStructure(neighborhoodStruct),
                       pivotingRule(pivotRule),
                       candidate(initMethod == InitializationMethod::RANDOM
                                    ? initialization::random(instance, rng)
                                    : initialization::simplifiedRZ(instance))
                       {

}

Solution FlowShopII::run() {
    switch(pivotingRule) {
        case PivotingRule::BEST_IMPROVEMENT:
            return runBestImprovement();
        case PivotingRule::FIRST_IMPROVEMENT:
            return runFirstImprovement();
    }
}

Solution FlowShopII::runBestImprovement() {
    Solution best = candidate;
    bool improved = true;
    while(improved) {
        improved = false;
        for(uint8_t i = 0; i < candidate.size(); i++) {
            for(uint8_t j = i + 1; j < candidate.size(); j++) {
                getNeighbour(i, j);
                if(candidate.cost() < best.cost()) {
                    best = candidate;
                    improved = true;
                }
            }
        }
    }
    return best;
}

void FlowShopII::getNeighbour(uint8_t i, uint8_t j) {
    switch(neighbourhoodStructure) {
        case NeighbourhoodStructure::TRANSPOSE:
            candidate.transpose(i);
        case NeighbourhoodStructure::EXCHANGE:
            candidate.exchange(i, j);
        case NeighbourhoodStructure::INSERT:
            candidate.insert(i, j);
    }
}
