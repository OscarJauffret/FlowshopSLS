//
// Created by oscar on 09/03/2025.
//

/**
 * @file initialization.hpp
 * @brief The initialization namespace contains the functions to initialize the solution. The initialization functions
 * include random initialization and simplified RZ initialization.
 */

#include "solution.hpp"
#include <random>
#include <algorithm>
#include <numeric>

namespace initialization {

    inline Solution random(const Instance& instance, std::mt19937& rng) {
        uint8_t jobs = instance.jobs;
        vector<uint8_t> permutation(jobs);
        std::iota(permutation.begin(), permutation.end(), 0);
        std::shuffle(permutation.begin(), permutation.end(), rng);

        return {instance, permutation};
    }

    inline Solution simplifiedRZ(const Instance& instance) {
        // TODO
        return {instance, {}};
    }
}