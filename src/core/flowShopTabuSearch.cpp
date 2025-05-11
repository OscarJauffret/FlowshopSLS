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

bool FlowShopTabuSearch::shouldStop(int generations, steady_clock::time_point start, int timeLimit) const {
    // The thing is that a time limit can either come from the user, when he sets maxGenerations to 0, in which case there should be no time limit
    // But the memetic algorithm can also set a time limit, in which case this time limit prevails over maxGenerations = 0.
    // The timeLimit parameter cannot be set by the user, it is set by the memetic algorithm
    int elapsed = duration_cast<milliseconds>(steady_clock::now() - start).count();

    // 1: If both limits are set, we stop when we reach either of them
    if (maxGenerations > 0 && timeLimit != -1) {
        return generations >= maxGenerations || elapsed >= timeLimit;
    }

    // 2: If maxGenerations is set, but not timeLimit, we stop when we reach maxGenerations
    if (maxGenerations > 0 && timeLimit == -1) {
        return generations >= maxGenerations;
    }

    // 3: If timeLimit is set, but not maxGenerations, we stop when we reach the time limit
    // This is the case when the user sets maxGenerations to 0, but the memetic algorithm sets a time limit
    // This never happens in the current implementation because if the memetic calls the tabu search, it sets
    // maxGenerations to a value greater than 0 to limit the number of generations
    if (maxGenerations == 0 && timeLimit != -1) {
        return elapsed >= timeLimit;
    }

    // 4: If neither limit is set, we don't stop
    if (maxGenerations == 0 && timeLimit == -1) {
        return false;
    }

    return false;
}

Solution FlowShopTabuSearch::run(int timeLimit) {
    int generations = 0;
    int stuck = 0;
    insertIterator.setSolution(candidate);

    auto start = steady_clock::now();

    while (!shouldStop(generations, start, timeLimit)) {
        // Neighborhood search procedure
        pair<pair<int, int>, Solution> bestNeighbor = {{-1, -1}, candidate};
        vector<pair<pair<int, int>, uint64_t>> allNeighbors;
        bool firstNeighbor = true;
        while (insertIterator.hasNext()) {
            uint8_t from = insertIterator.getFrom();
            uint8_t to = insertIterator.getTo();
            Solution neighbor = insertIterator.next();

            if (!isTabu(from, to) || neighbor < candidate) {
                if (firstNeighbor || neighbor < bestNeighbor.second) {
                    // If the neighbor is the first one or better than the best one, update the best neighbor
                    // If we do not check if the neighbor is the first one, we would only consider the neighbors
                    // that lead to a better solution than the current one because bestNeighbor is initialized with the current solution
                    bestNeighbor = {{from, to}, neighbor};
                }
                firstNeighbor = false;
            }
            allNeighbors.emplace_back(std::make_pair(from, to), neighbor.getFitness());

        }
        if (bestNeighbor.first.first != -1 && bestNeighbor.first.second != -1) {
            int from = bestNeighbor.first.first;
            int to = bestNeighbor.first.second;
            addToTabuList(from, to);  // Add the move to the tabu list

            if (bestNeighbor.second < candidate) {
                candidate = bestNeighbor.second;
                stuck = 0;
            } else {
                stuck++;
                if (stuck >= maxStuck) {
                    if (allNeighbors.size() > 1) {
                        std::sort(allNeighbors.begin(), allNeighbors.end(), [](const auto& a, const auto& b) {
                            return a.second < b.second;
                        });
                        std::uniform_int_distribution<> dist(1, std::min(config::memetic::tabu::neighborsConsideredInPerturbation,
                                        static_cast<int>(allNeighbors.size()) - 1));
                        int selected = dist(rng);
                        int f = allNeighbors[selected].first.first;
                        int t = allNeighbors[selected].first.second;
                        Solution recomputed = candidate.insert(f, t);
                        candidate = recomputed;
                    } else {
                        candidate = bestNeighbor.second;
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
