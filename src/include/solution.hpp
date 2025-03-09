//
// Created by oscar on 09/03/2025.
//

#ifndef FLOWSHOPSLS_SOLUTION_HPP
#define FLOWSHOPSLS_SOLUTION_HPP

#include "instance.hpp"

class Solution {
    private:
        const Instance& instance;
        vector<uint8_t> permutation;
        uint64_t totalCompletionTime = 0;

    public:
        Solution(const Instance& instance, const vector<uint8_t>& permutation);
        uint64_t evaluate();
        uint64_t updateEvaluation(uint8_t job, uint8_t position);
        friend ostream &operator<<(ostream &os, const Solution &solution);

};


#endif //FLOWSHOPSLS_SOLUTION_HPP
