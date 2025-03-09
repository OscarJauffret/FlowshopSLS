//
// Created by oscar on 09/03/2025.
//

#ifndef FLOWSHOPSLS_INSTANCE_HPP
#define FLOWSHOPSLS_INSTANCE_HPP

#include <cstdint>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::ostream;

/**
 * @struct Instance
 * @brief Structure that represents an instance of the Flowshop Scheduling Problem
 */
struct Instance {
    uint8_t jobs = 0;       // Number of jobs
    uint8_t machines = 0;   // Number of machines
    vector<vector<uint8_t>> processingTimes;    // Processing times for each job in each machine

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
