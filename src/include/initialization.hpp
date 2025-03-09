//
// Created by oscar on 09/03/2025.
//

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