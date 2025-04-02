//
// Created by oscar on 15/03/2025.
//

#include "../../include/initialization/initialization.hpp"

#include <iostream>

Solution initialization::random(const Instance &instance, std::mt19937 &rng) {
    uint8_t jobs = instance.jobs;
    vector<uint8_t> permutation(jobs);
    std::iota(permutation.begin(), permutation.end(), 0);           // Fill the permutation with the values 0, 1, 2, ..., jobs - 1
    std::shuffle(permutation.begin(), permutation.end(), rng);       // Shuffle the permutation

    return {instance, permutation};
}

Solution initialization::simplifiedRZ(const Instance &instance, std::mt19937 &rng) {
    uint8_t jobs = instance.jobs;
    vector<uint8_t> permutation(jobs);
    std::iota(permutation.begin(), permutation.end(), 0);           // Fill the permutation with the values 0, 1, 2, ..., jobs - 1

    // Start by ordering the jobs by the sum of their processing times
    vector<uint64_t> sumOfProcessingTimes(jobs);
    for (uint8_t job = 0; job < jobs; job++) {
        sumOfProcessingTimes[job] = std::accumulate(instance.processingTimes[job].begin(), instance.processingTimes[job].end(), 0ULL);
    }

    // Sort the permutation by the sum of the processing times (sort the indexes)
    std::sort(permutation.begin(), permutation.end(), [&](uint8_t i, uint8_t j) {
        return sumOfProcessingTimes[i] < sumOfProcessingTimes[j];
    });

    // Now we have the permutation ordered by the sum of the processing times
    // We will now apply the RZ heuristic
    vector<uint8_t> bestPermutation = permutation;
    for (uint8_t currentNumberOfJobs = 1; currentNumberOfJobs < jobs; currentNumberOfJobs++) {
        uint64_t bestCost = std::numeric_limits<uint64_t>::max();
        permutation = bestPermutation;
        vector<vector<uint8_t>> candidates; // This vector will hold all the candidates that have the same minimal cost

        for (uint8_t insert_position = 0; insert_position <= currentNumberOfJobs; insert_position++) {
            Solution candidate(instance, permutation);
            candidate = candidate.insert(currentNumberOfJobs, insert_position, currentNumberOfJobs + 1);
            uint64_t cost = candidate.getFitness();
            if (cost < bestCost) {
                bestCost = cost;
                candidates.clear();
                candidates.push_back(candidate.getPermutation());
            } else if (cost == bestCost) {
                candidates.push_back(candidate.getPermutation());
            }
        }

        // If there are multiple candidates with the same cost, we choose one randomly
        std::uniform_int_distribution<> dist(0, static_cast<int>(candidates.size()) - 1);
        bestPermutation = candidates[dist(rng)];
    }

    return {instance, bestPermutation};
}