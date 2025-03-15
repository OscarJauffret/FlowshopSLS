//
// Created by oscar on 15/03/2025.
//

#include "include/flowShopII.hpp"

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
    //TODO: implement
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
