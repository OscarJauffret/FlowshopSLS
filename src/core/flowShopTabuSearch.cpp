//
// Created by oscar on 06/05/2025.
//

#include "../../include/core/flowShopTabuSearch.hpp"
#include "../../include/initialization/initialization.hpp"
#include "../config.hpp"

FlowShopTabuSearch::FlowShopTabuSearch(const Instance &instance, int tabuTenure, int alpha, int maxGenerations, int maxStuck, std::mt19937 &rng)
                                       : candidate(initialization::random(instance, rng)), tabuTenure(tabuTenure), alpha(alpha),
                                         maxGenerations(maxGenerations), maxStuck(maxStuck), insertIterator(candidate, alpha), rng(rng) {

}

bool FlowShopTabuSearch::isTabu(int from, int to) {
    return std::find(tabuList.begin(), tabuList.end(), std::make_pair(from, to)) != tabuList.end();
}

void FlowShopTabuSearch::addToTabuList(pair<int, int> fromToPair) {
    tabuList.emplace_back(fromToPair);
    if (tabuList.size() > tabuTenure) {
        tabuList.pop_front();
    }
}

Solution FlowShopTabuSearch::run() {
    int generations = 0;
    int stuck = 0;

    while (generations < maxGenerations) {
        // Neighborhood search procedure, finds the best neighbor
        vector<pair<pair<int, int>, Solution>> neighbors;
        while (insertIterator.hasNext()) {
            uint8_t from = insertIterator.getFrom();
            uint8_t to = insertIterator.getTo();
            Solution neighbor = insertIterator.next();
            // Check if the move is tabu, but if the neighbor is better than the candidate, we can consider it
            if (!isTabu(from, to) || neighbor < candidate) {
                neighbors.emplace_back(std::make_pair(from, to), neighbor);
            }
        }
        // Sort the neighbors by fitness
        std::sort(neighbors.begin(), neighbors.end(), [](const auto &a, const auto &b) {
            return a.second.getFitness() < b.second.getFitness();
        });

        addToTabuList(neighbors[0].first);  // Add the move to the tabu list

        if (neighbors[0].second < candidate) {   // Means we found a better neighbor
            candidate = neighbors[0].second;
            stuck = 0;
        } else {
            stuck++;
            if (stuck >= maxStuck) {
                // If stuck, choose a new candidate randomly from the best neighbors, without considering the tabu list
                std::uniform_int_distribution<> dist(1, std::min(config::memetic::tabu::neighborsConsideredInPerturbation, (int)neighbors.size() - 1));
                candidate = neighbors[dist(rng)].second; // Choose a random neighbor from the list of neighbors
                stuck = 0;
            }
        }
        generations++;
        insertIterator.setSolution(candidate); // Reset the iterator with the candidate solution (possibly changed)
    }
    return candidate;
}
