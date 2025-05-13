//
// Created by oscar on 01/04/2025.
//

#include "../../include/core/flowShopVnd.hpp"

FlowShopVND::FlowShopVND(const Instance &instance, VNDStrategy neighbourhoodOrder, std::mt19937 rng)
                        : FlowShopSLS(instance, PivotingRule::FIRST_IMPROVEMENT,
                                      InitializationMethod::SIMPLIFIED_RZ, rng) {
    switch(neighbourhoodOrder) {
        case VNDStrategy::TEI:
            neighbourhoodIterators.push_back(std::make_unique<TransposeIterator>(candidate));
            neighbourhoodIterators.push_back(std::make_unique<ExchangeIterator>(candidate));
            neighbourhoodIterators.push_back(std::make_unique<InsertIterator>(candidate));
            break;
        case VNDStrategy::TIE:
            neighbourhoodIterators.push_back(std::make_unique<TransposeIterator>(candidate));
            neighbourhoodIterators.push_back(std::make_unique<InsertIterator>(candidate));
            neighbourhoodIterators.push_back(std::make_unique<ExchangeIterator>(candidate));
            break;
    }
}

Solution FlowShopVND::step() {
    Solution current = candidate;

    // Iterate through the neighbourhoods.
    for (auto &neighborhoodIterator : neighbourhoodIterators) {
        neighborhoodIterator->setSolution(current, true);     // Set the current solution to the iterator.

        while (neighborhoodIterator->hasNext()) {
            Solution neighbor = neighborhoodIterator->next();

            if (neighbor.getFitness() < current.getFitness()) {
                return neighbor;
            }
        }
    }
    // If no improvement is found, return the current solution.
    return current;
}
