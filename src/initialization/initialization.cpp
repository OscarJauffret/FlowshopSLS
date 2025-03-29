//
// Created by oscar on 15/03/2025.
//

#include "../../include/initialization/initialization.hpp"

#include <iostream> // TODO; Remove this line
/**
 * @brief The random function initializes the solution with a random permutation of the jobs.
 * @param instance The instance of the problem.
 * @param rng The random number generator.
 * @return The solution with a random permutation of the jobs.
 */
Solution initialization::random(const Instance &instance, std::mt19937 &rng) {
    uint8_t jobs = instance.jobs;
    vector<uint8_t> permutation(jobs);
    std::iota(permutation.begin(), permutation.end(), 0);           // Fill the permutation with the values 0, 1, 2, ..., jobs - 1
    std::shuffle(permutation.begin(), permutation.end(), rng);       // Shuffle the permutation

    return {instance, permutation};
}

/**
 * @brief The simplifiedRZ function initializes the solution with the simplified RZ heuristic.
 * @param instance The instance of the problem.
 * @return The solution with the simplified RZ heuristic.
 */
Solution initialization::simplifiedRZ(const Instance &instance) {
    uint8_t jobs = instance.jobs;
    vector<uint8_t> permutation(jobs);
    std::iota(permutation.begin(), permutation.end(), 0);           // Fill the permutation with the values 0, 1, 2, ..., jobs - 1

    // Start by ordering the jobs by the sum of their processing times
    vector<uint64_t> sumOfProcessingTimes(jobs);
    for (uint8_t job = 0; job < jobs; job++) {
        sumOfProcessingTimes[job] = std::accumulate(instance.processingTimes[job].begin(), instance.processingTimes[job].end(), 0ULL);
    }

    std::sort(permutation.begin(), permutation.end(), [&](uint8_t i, uint8_t j) {
        return sumOfProcessingTimes[i] < sumOfProcessingTimes[j];
    });

    // Now we have the permutation ordered by the sum of the processing times
    // We will now apply the RZ heuristic
    for (uint8_t i = 0; i < jobs; i++) {
        std::cout << (int) permutation[i] << " ";
    }
    std::cout << std::endl;
    vector<uint8_t> bestPermutation = permutation;
    for (uint8_t currentNumberOfJobs = 1; currentNumberOfJobs < jobs; currentNumberOfJobs++) {
        uint64_t bestCost = std::numeric_limits<uint64_t>::max();
        permutation = bestPermutation;
        for (uint8_t insert_position = 0; insert_position <= currentNumberOfJobs; insert_position++) {
            Solution candidate(instance, permutation);
            candidate = candidate.insert(currentNumberOfJobs, insert_position);
            uint64_t candidateCost = candidate.evaluate(currentNumberOfJobs + 1);
            std::cout << "Candidate: " << candidate << std::endl;
            if (candidateCost < bestCost) {
                std::cout << "Candidate cost is better" << std::endl;
                bestCost = candidateCost;
                bestPermutation = candidate.getPermutation();
            }
        }
    }


    return {instance, bestPermutation};
}