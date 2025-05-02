//
// Created by oscar on 09/03/2025.
//

#include "../../include/core/solution.hpp"
#include <iostream>

using std::endl;
using std::cout;

Solution::Solution(const Instance& instance, const vector<uint8_t>& permutation) : instance(instance), permutation(permutation) {
    completionTimes = vector<vector<uint64_t>>(instance.jobs, vector<uint64_t>(instance.machines, 0));
    evaluate(0);
}

void Solution::evaluate(uint8_t from, uint8_t upTo) {
    if (upTo == 0) {    // If upTo is 0, we evaluate all the jobs
        upTo = instance.jobs;
    }
    const uint8_t m = instance.machines;

    for (uint8_t jobIdx = from; jobIdx < upTo; jobIdx++) {
        uint8_t job = permutation[jobIdx];  // Get the job from the permutation
        for (uint8_t machine = 0; machine < m; machine++) {
            uint64_t prevJobCompletion = (jobIdx > 0) ? completionTimes[jobIdx - 1][machine] : 0;       // Get the completion time of the previous job
            uint64_t prevMachineCompletion = (machine > 0) ? completionTimes[jobIdx][machine - 1] : 0;  // Get the completion time of the previous machine

            // The completion time of the job in the machine is the maximum between the completion time of the previous job in the machine and the completion time of the job in the previous machine plus the processing time
            completionTimes[jobIdx][machine] = std::max(prevJobCompletion, prevMachineCompletion) + instance.processingTimes[job][machine];
        }
    }

    sumOfCompletionTimes = 0;
    for (uint8_t jobIdx = 0; jobIdx < upTo; jobIdx++) {
        sumOfCompletionTimes += completionTimes[jobIdx][m - 1];
    }

}


Solution Solution::transpose(uint8_t i) const{
    return exchange(i, i + 1);  // Transpose is the same as exchanging two consecutive jobs
}

Solution Solution::exchange(uint8_t i, uint8_t j) const {
    Solution neighbor(*this);    // Create a copy of the current solution
    std::swap(neighbor.permutation[i], neighbor.permutation[j]);    // Swap the jobs
    neighbor.evaluate(std::min(i, j));  // Evaluate the new solution, only the jobs that changed need to be evaluated
    return neighbor;
}

Solution Solution::insert(uint8_t from, uint8_t to, uint8_t calculateFitnessUpTo, bool calculateFitness) const {
    Solution neighbor(*this);       // Create a copy of the current solution
    uint8_t job = neighbor.permutation[from];

    // Remove the job from the permutation and insert it in the new position
    neighbor.permutation.erase(neighbor.permutation.begin() + from);
    neighbor.permutation.insert(neighbor.permutation.begin() + to, job);
    if (calculateFitness) {
        neighbor.evaluate(std::min(from, to), calculateFitnessUpTo);    // Evaluate the new solution, only the jobs that changed need to be evaluated
    }
    return neighbor;
}

uint64_t Solution::getFitness() const {
    return sumOfCompletionTimes;
}

uint8_t Solution::getNumberOfJobs() const {
    return instance.jobs;
}

const vector<uint8_t> &Solution::getPermutation() const {
    return permutation;
}

void Solution::setPermutation(const vector<uint8_t>& permutation) {
    this->permutation = permutation;
}

ostream &operator<<(ostream &os, const Solution &solution) {
    os << "Solution: " << solution.sumOfCompletionTimes << endl;
    os << "Permutation: ";
    for (int job : solution.permutation) {
        os << job << " ";
    }
    return os;
}

Solution &Solution::operator=(const Solution &other) {
    if (this != &other) {
        if (&instance != &other.instance) {
            throw std::logic_error("Cannot assign solutions from different instances");
        }
        permutation = other.permutation;
        sumOfCompletionTimes = other.sumOfCompletionTimes;
        completionTimes = other.completionTimes;
    }
    return *this;
}

bool Solution::operator<(const Solution& other) const {
    return this->sumOfCompletionTimes < other.sumOfCompletionTimes;
}