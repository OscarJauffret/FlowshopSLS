//
// Created by oscar on 09/03/2025.
//

/**
 * @file instance.hpp
 * @brief Implementation of the Instance class. This class represents an instance of the Flowshop Scheduling Problem.
 * It contains the number of jobs, the number of machines, and the processing times for each job in each machine.
 * This is not the class that stores the solution, it is only used to load the instances from a file.
 *
 * @see instance.cpp
 */

#ifndef FLOWSHOPSLS_INSTANCE_HPP
#define FLOWSHOPSLS_INSTANCE_HPP

#include <cstdint>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::ostream;

/**
 * @file instance.hpp
 * @struct Instance
 * @brief Structure that represents an instance of the Flowshop Scheduling Problem
 * @field jobs - Number of jobs
 * @field machines - Number of machines
 * @field processingTimes - Processing times for each job in each machine [job][machine]
 *
 * @see instance.cpp
 */
struct Instance {
    uint8_t jobs = 0;       // Number of jobs
    uint8_t machines = 0;   // Number of machines
    vector<vector<uint8_t>> processingTimes;    // Processing times for each job in each machine [job][machine]

    /**
     * @brief Load an instance from a file
     * @param filename Path to the instance file (has to be in the format described in the instructions)
     * @return Instance
     */
    explicit Instance(const string& filename);

    /**
     * @brief Overload of the << operator to print an instance, it is useful for debugging
     * @param os The output stream
     * @param instance The instance to print
     * @return The output stream
     */
    friend ostream& operator<<(ostream& os, const Instance& instance);

};

#endif //FLOWSHOPSLS_INSTANCE_HPP
