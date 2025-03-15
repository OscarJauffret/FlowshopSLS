//
// Created by oscar on 09/03/2025.
//

/**
 * @file instance.cpp
 * @brief Implementation of the Instance class. This class represents an instance of the Flowshop Scheduling Problem.
 * It contains the number of jobs, the number of machines, and the processing times for each job in each machine.
 * This is not the class that stores the solution, it is only used to load the instances from a file.
 *
 * @see instance.hpp
 */

#include <fstream>
#include <iostream>

#include "include/instance.hpp"

using std::ifstream;
using std::cerr;
using std::endl;
using std::cout;

/**
 * @brief Load an instance from a file
 * @param filename Path to the instance file (has to be in the format described in the instructions)
 * @return Instance
 */
Instance::Instance(const std::string& filename) {
    ifstream instanceFile(filename);

    if (!instanceFile.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    int numJobs, numMachines;
    instanceFile >> numJobs >> numMachines;

    if (numJobs > 255 || numMachines > 255) {
        cerr << "The number of jobs and machines must be less than 256" << endl;
        return;
    }

    jobs = static_cast<uint8_t>(numJobs);
    machines = static_cast<uint8_t>(numMachines);

    processingTimes.resize(jobs, vector<uint8_t>(machines));

    // Read the processing times for each job in each machine
    for (int i = 0; i < jobs; ++i) {
        for (int j = 0; j < machines; ++j) {
            int machineNumber, processingTime;
            instanceFile >> machineNumber >> processingTime;
            processingTimes[i][j] = static_cast<uint8_t>(processingTime);
        }
    }
    instanceFile.close();
}

/**
 * @brief Overload of the << operator to print an instance
 * @param os The output stream
 * @param instance The instance to print
 * @return The output stream
 */
ostream& operator<<(ostream& os, const Instance& instance) {
    os << "Jobs: " << static_cast<int>(instance.jobs) << endl;
    os << "Machines: " << static_cast<int>(instance.machines) << endl;
    os << "Processing times:" << endl;
    for (int i = 0; i < instance.jobs; ++i) {
        for (int j = 0; j < instance.machines; ++j) {
            os << static_cast<int>(instance.processingTimes[i][j]) << " ";
        }
        os << endl;
    }
    return os;
}