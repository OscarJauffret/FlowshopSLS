//
// Created by oscar on 01/04/2025.
//

#include "../../include/core/flowShopVnd.hpp"

FlowShopVND::FlowShopVND(const Instance &instance, VNDStrategy neighborhoodOrder, std::mt19937 rng)
                        : FlowShopSLS(instance, PivotingRule::FIRST_IMPROVEMENT,
                                      InitializationMethod::SIMPLIFIED_RZ, rng) {

    switch(neighborhoodOrder) {
        case VNDStrategy::TEI:
            neighborhoodIterators.push_back(std::make_unique<TransposeIterator>(candidate));
            neighborhoodIterators.push_back(std::make_unique<ExchangeIterator>(candidate));
            neighborhoodIterators.push_back(std::make_unique<InsertIterator>(candidate));
            break;
        case VNDStrategy::TIE:
            neighborhoodIterators.push_back(std::make_unique<TransposeIterator>(candidate));
            neighborhoodIterators.push_back(std::make_unique<InsertIterator>(candidate));
            neighborhoodIterators.push_back(std::make_unique<ExchangeIterator>(candidate));
            break;
    }
}

Solution FlowShopVND::step() {
    Solution current = candidate;

    // Iterate through the neighborhoods.
    for (auto &neighborhoodIterator : neighborhoodIterators) {
        neighborhoodIterator->setSolution(current);     // Set the current solution to the iterator.

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
