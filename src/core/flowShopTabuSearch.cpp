//
// Created by oscar on 06/05/2025.
//

#include "../../include/core/flowShopTabuSearch.hpp"
#include "../../include/initialization/initialization.hpp"

FlowShopTabuSearch::FlowShopTabuSearch(const Instance &instance, int tabuTenure, int alpha, int maxGenerations, int maxStuck, std::mt19937 &rng)
                                       : candidate(initialization::random(instance, rng)), tenure(tabuTenure), alpha(alpha),
                                       maxGenerations(maxGenerations), maxStuck(maxStuck) {

}

Solution FlowShopTabuSearch::run() {
    int generations = 0;
    int stuck = 0;

    while (generations < maxGenerations) {

    }
    return candidate;
}
