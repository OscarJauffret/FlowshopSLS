//
// Created by oscar on 15/03/2025.
//

#include "../../include/initialization/initialization.hpp"

/**
 * @brief The random function initializes the solution with a random permutation of the jobs.
 * @param instance The instance of the problem.
 * @param rng The random number generator.
 * @return The solution with a random permutation of the jobs.
 */
Solution initialization::random(const Instance &instance, std::mt19937 &rng) {
    uint8_t jobs = instance.jobs;
    vector<uint8_t> permutation(jobs);
    std::iota(permutation.begin(), permutation.end(), 0);
    std::shuffle(permutation.begin(), permutation.end(), rng);

    return {instance, permutation};
}

/**
 * @brief The simplifiedRZ function initializes the solution with the simplified RZ heuristic.
 * @param instance The instance of the problem.
 * @return The solution with the simplified RZ heuristic.
 */
Solution initialization::simplifiedRZ(const Instance &instance) {
    //TODO: Implement the simplified RZ heuristic

    return {instance, {}};
}