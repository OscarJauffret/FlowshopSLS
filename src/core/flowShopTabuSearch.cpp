//
// Created by oscar on 06/05/2025.
//

#include "../../include/core/flowShopTabuSearch.hpp"
#include "../../include/initialization/initialization.hpp"
#include "../../include/utils/memeticTimeLimitProvider.hpp"
#include "../config.hpp"
#include <chrono>

namespace chrono = std::chrono;
using chrono::steady_clock;
using chrono::milliseconds;
using chrono::duration_cast;


FlowShopTabuSearch::FlowShopTabuSearch(const Instance &instance, int tabuTenure, int alpha, int maxGenerations, int maxStuck, std::mt19937 &rng)
                                       : candidate(initialization::simplifiedRZ(instance, rng)), tabuTenure(tabuTenure),
                                         maxGenerations(maxGenerations), maxStuck(maxStuck), insertIterator(candidate, alpha), rng(rng) {

}

bool FlowShopTabuSearch::isTabu(int from, int to) {
    // The strategy is the one from Nowicki, E. and Smutnicki, C
    // If from < to, a move (from, to) is tabu if the tabu list contains at least a pair (permutation[j], permutation[from]), where j is in [from + 1, to]
    // If from > to, a move (from, to) is tabu if the tabu list contains at least a pair (permutation[from], permutation[j]), where j is in [to, from - 1]
    const auto& permutation = candidate.getPermutation();

    if (from < to) {
        for (int j = from + 1; j <= to; j++) {
            std::pair<uint8_t, uint8_t> checkPair = {permutation[j], permutation[from]};
            if (std::find(tabuList.begin(), tabuList.end(), checkPair) != tabuList.end()) {
                return true;
            }
        }
    } else if (from > to) {
        for (int j = to; j < from; j++) {
            std::pair<uint8_t, uint8_t> checkPair = {permutation[from], permutation[j]};
            if (std::find(tabuList.begin(), tabuList.end(), checkPair) != tabuList.end()) {
                return true;
            }
        }
    }
    return false;
}

void FlowShopTabuSearch::addToTabuList(int from, int to) {
    // The strategy is the one from Nowicki, E. and Smutnicki, C
    vector<uint8_t> permutation = candidate.getPermutation();
    if (from < to && from + 1 < permutation.size()) {
        tabuList.emplace_back(permutation[from], permutation[from + 1]);
    } else if (from > to && from > 0) {
        tabuList.emplace_back(permutation[from - 1], permutation[from]);
    }
    if (tabuList.size() > tabuTenure) {
        tabuList.pop_front();
    }
}

Solution FlowShopTabuSearch::run() {
    int generations = 0;
    int stuck = 0;
    insertIterator.setSolution(candidate);

    int allowedTime = 0;
    auto start = steady_clock::now();

    if (maxGenerations == 0) {
        allowedTime = MemeticTimeLimitProvider::getMemeticAllowedTime(candidate.getNumberOfJobs());
    }

    while ((maxGenerations > 0 && generations < maxGenerations) ||
           (maxGenerations == 0 && duration_cast<milliseconds>(steady_clock::now() - start).count() < allowedTime)) {
        // Neighborhood search procedure
        vector<pair<pair<int, int>, Solution>> neighbors;
        vector<pair<pair<int, int>, Solution>> allNeighbors;
        while (insertIterator.hasNext()) {
            uint8_t from = insertIterator.getFrom();
            uint8_t to = insertIterator.getTo();
            Solution neighbor = insertIterator.next();
            // Check if the move is tabu, but if the neighbor is better than the candidate, we can consider it
            if (!isTabu(from, to) || neighbor < candidate) {
                neighbors.emplace_back(std::make_pair(from, to), neighbor);
            }
            allNeighbors.emplace_back(std::make_pair(from, to), neighbor);
        }
        // Sort the neighbors by fitness
        std::sort(neighbors.begin(), neighbors.end(), [](const auto &a, const auto &b) {
            return a.second.getFitness() < b.second.getFitness();
        });

        if (!neighbors.empty()) {
            int from = neighbors[0].first.first;
            int to = neighbors[0].first.second;
            addToTabuList(from, to);  // Add the move to the tabu list

            if (neighbors[0].second < candidate) {   // Means we found a better neighbor
                candidate = neighbors[0].second;
                stuck = 0;
            } else {
                stuck++;
                if (stuck >= maxStuck) {
                    if (allNeighbors.size() > 1) {
                        std::sort(allNeighbors.begin(), allNeighbors.end(), [](const auto &a, const auto &b) {
                            return a.second.getFitness() < b.second.getFitness();
                        });
                        std::uniform_int_distribution<> dist(
                            1, std::min(config::memetic::tabu::neighborsConsideredInPerturbation, (int) allNeighbors.size() - 1)
                        );
                        candidate = allNeighbors[dist(rng)].second;
                    } else {
                        candidate = allNeighbors[0].second;
                    }
                    stuck = 0;
                }
            }
        }
        generations++;
        insertIterator.setSolution(candidate); // Reset the iterator with the candidate solution (possibly changed)
    }
    tabuList.clear(); // Clear the tabu list at the end of the search
    return candidate;
}
