//
// Created by oscar on 09/03/2025.
//

/**
 * @file solution.cpp
 * @brief The solution class is the class that will contain the current candidate solution to the given instance.
 *
 * @see solution.hpp
 */

#include "include/solution.hpp"
#include <iostream>

using std::endl;
using std::cout;

Solution::Solution(const Instance& instance, const vector<uint8_t>& permutation) : instance(instance), permutation(permutation) {
    evaluate();
}

ostream &operator<<(ostream &os, const Solution &solution) {
    os << "Solution: " << solution.sumOfCompletionTimes << endl;
    os << "Permutation: ";
    for (int job : solution.permutation) {
        os << job << " ";
    }
    return os;
}

uint64_t Solution::evaluate() {
    vector<vector<uint64_t>> completionTimes(instance.machines, vector<uint64_t>(instance.jobs, 0));

    for (int i = 0; i < instance.machines; i++) {       // First job
        if (i == 0) {
            completionTimes[i][0] = instance.processingTimes[permutation[0]][0];
        } else {
            completionTimes[i][0] = completionTimes[i - 1][0] + instance.processingTimes[permutation[0]][i];
        }
    }

    for (int i = 1; i < instance.jobs; i++) {       // First machine
        completionTimes[0][i] = completionTimes[0][i - 1] + instance.processingTimes[permutation[i]][0];
    }

    for (int i = 1; i < instance.machines; i++) {
        for (int j = 1; j < instance.jobs; j++) {
            // The completion time is given by the following.
            // First, the job can go into machine i after both of the following conditions are met:
            // - The job is already done in machine i - 1
            // - The previous job is already done in machine i
            // Then, we add the processing time of the job in machine i
            completionTimes[i][j] = std::max(completionTimes[i - 1][j], completionTimes[i][j - 1]) + instance.processingTimes[permutation[j]][i];
        }
    }

    sumOfCompletionTimes = 0;
    for (int i = 0; i < instance.jobs; i++) {
        sumOfCompletionTimes += completionTimes[instance.machines - 1][i];
    }
    return 0;
}

uint64_t Solution::updateEvaluation(uint8_t job, uint8_t position) {    //TODO: Implement this
    return 0;
}
