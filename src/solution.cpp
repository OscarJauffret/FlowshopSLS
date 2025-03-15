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
    const uint8_t n = instance.jobs;
    const uint8_t m = instance.machines;

    vector<uint64_t> prevCompletion(m, 0);  // Stores the completion time of the previous job in each machine
    vector<uint64_t> currCompletion(m, 0);  // Stores the completion time of the current job in each machine

    sumOfCompletionTimes = 0;

    for (uint8_t jobIdx = 0; jobIdx < n; jobIdx++) {
        for (uint8_t machineIdx = 0; machineIdx < m; machineIdx++) {

            uint64_t completionPrevMachine = (machineIdx > 0) ? currCompletion[machineIdx - 1] : 0;
            uint64_t completionPrevJob = prevCompletion[machineIdx];    // If this is the first job, the completion time of the previous job is 0 because we initialized it that way

            currCompletion[machineIdx] = std::max(completionPrevMachine, completionPrevJob) + instance.processingTimes[permutation[jobIdx]][machineIdx];
        }

        sumOfCompletionTimes += currCompletion[m - 1];  // Add the completion time of this job
        std::swap(prevCompletion, currCompletion);  // The current completion times become the previous completion times
    }

    return sumOfCompletionTimes;
}


uint64_t Solution::updateEvaluation(uint8_t job, uint8_t position) {    //TODO: Implement this
    return 0;
}
