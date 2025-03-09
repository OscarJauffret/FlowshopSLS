//
// Created by oscar on 09/03/2025.
//

#include "include/solution.hpp"
#include <iostream>

using std::endl;

Solution::Solution(const Instance& instance, const vector<uint8_t>& permutation) : instance(instance), permutation(permutation) {
    evaluate();
}

ostream &operator<<(ostream &os, const Solution &solution) {
    os << "Solution: " << solution.totalCompletionTime << endl;
    os << "Permutation: ";
    for (int job : solution.permutation) {
        os << job << " ";
    }
    return os;
}

uint64_t Solution::evaluate() {
    totalCompletionTime = 80;       //TODO: Implement this
    return 0;
}

uint64_t Solution::updateEvaluation(uint8_t job, uint8_t position) {    //TODO: Implement this
    return 0;
}
