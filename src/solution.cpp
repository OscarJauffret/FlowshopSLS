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


Solution Solution::transpose(uint8_t i) const{
    return exchange(i, i + 1);
}

Solution Solution::exchange(uint8_t i, uint8_t j) const {
    Solution neighbor(*this);
    std::swap(neighbor.permutation[i], neighbor.permutation[j]);
    neighbor.evaluate();    //TODO: should not recompute the whole thing
    return neighbor;
}

Solution Solution::insert(uint8_t from, uint8_t to) const {
    Solution neighbor(*this);
    uint8_t job = neighbor.permutation[from];
    neighbor.permutation.erase(neighbor.permutation.begin() + from);
    neighbor.permutation.insert(neighbor.permutation.begin() + to, job);
    neighbor.evaluate();    //TODO: should not recompute the whole thing
    return neighbor;
}

uint64_t Solution::getFitness() const {
    return sumOfCompletionTimes;
}

ostream &operator<<(ostream &os, const Solution &solution) {
    os << "Solution: " << solution.sumOfCompletionTimes << endl;
    os << "Permutation: ";
    for (int job : solution.permutation) {
        os << job << " ";
    }
    return os;
}
