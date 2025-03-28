//
// Created by oscar on 09/03/2025.
//


#ifndef FLOWSHOPSLS_SOLUTION_HPP
#define FLOWSHOPSLS_SOLUTION_HPP

#include "instance.hpp"

/**
 * @file solution.hpp
 * @brief The solution class is the class that will contain the current candidate solution to the given instance.
 * @field instance - The instance of the problem.
 * @field permutation - The permutation of the jobs.
 * @field sumOfCompletionTimes - The sum of the completion times of the jobs in the permutation.
 *
 * @see solution.cpp
 */

class Solution {
    private:
        const Instance& instance;
        vector<uint8_t> permutation;
        uint64_t sumOfCompletionTimes = 0;

    public:
        /**
         * @brief The constructor of the Solution class. It initializes the solution with a given problem instance and a permutation of the jobs.
         * @param instance The instance of the problem.
         * @param permutation The permutation of the jobs.
         */
        Solution(const Instance& instance, const vector<uint8_t>& permutation);

        /**
         * @brief The evaluate function calculates the sum of the completion times of the jobs in the permutation.
         * @return The sum of the completion times of the jobs in the permutation.  //TODO: necessary to return?
         */
        uint64_t evaluate();

        /**
         * @brief The updateEvaluation function updates the sum of the completion times of the jobs in the permutation after a change in the permutation.
         * @param job The job that was moved.
         * @param position The position where the job was moved.
         * @return The sum of the completion times of the jobs in the permutation after the change.  //TODO: necessary to return?
         */
        uint64_t updateEvaluation(uint8_t job, uint8_t position);

        /**
         * @brief The transpose function transposes two consecutive jobs in the permutation. It creates a new solution with the transposed jobs.
         * @param i The index of the job to transpose. It will be transposed with the next job.
         * @return A new solution with the transposed jobs.
         */
        Solution transpose(uint8_t i) const;

        /**
         * @brief The exchange function exchanges two jobs in the permutation. It creates a new solution with the exchanged jobs.
         * @param i The index of the first job to exchange.
         * @param j The index of the second job to exchange.
         * @return A new solution with the exchanged jobs.
         */
        Solution exchange(uint8_t i, uint8_t j) const;

        /**
         * @brief The insert function inserts a job in a new position in the permutation. It creates a new solution with the inserted job.
         * @param from The index of the job to insert.
         * @param to The index where the job will be inserted.
         * @return A new solution with the inserted job.
         */
        Solution insert(uint8_t from, uint8_t to) const;

        /**
         * @brief The getFitness function returns the sum of the completion times of the jobs in the permutation.
         * @return The sum of the completion times of the jobs in the permutation.
         */
        uint64_t getFitness() const;

        /**
         * @brief The getNumberOfJobs function returns the number of jobs in the instance.
         * @return The number of jobs in the instance.
         */
         [[nodiscard]] uint8_t getNumberOfJobs() const;

        /**
         * @brief The << operator is overloaded to print the solution. It prints the sum of the completion times and the permutation of the jobs. This is useful for debugging.
         * @param os The output stream.
         * @param solution The solution to print.
         * @return The output stream with the solution printed.
         */
        friend ostream &operator<<(ostream &os, const Solution &solution);

        /**
         * @brief The copy constructor of the Solution class.
         * @param other The solution to copy.
         * @return The new solution.
         */
        Solution& operator=(const Solution& other);

};


#endif //FLOWSHOPSLS_SOLUTION_HPP
