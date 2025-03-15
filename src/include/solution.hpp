//
// Created by oscar on 09/03/2025.
//

/**
 * @file solution.hpp
 * @brief The solution class is the class that will contain the current candidate solution to the given instance.
 *
 * @see solution.cpp
 */

#ifndef FLOWSHOPSLS_SOLUTION_HPP
#define FLOWSHOPSLS_SOLUTION_HPP

#include "instance.hpp"

class Solution {
    private:
        const Instance& instance;
        vector<uint8_t> permutation;
        uint64_t sumOfCompletionTimes = 0;

    public:
        Solution(const Instance& instance, const vector<uint8_t>& permutation);
        uint64_t evaluate();
        uint64_t updateEvaluation(uint8_t job, uint8_t position);
        friend ostream &operator<<(ostream &os, const Solution &solution);

};


#endif //FLOWSHOPSLS_SOLUTION_HPP
