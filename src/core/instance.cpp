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

#include "../../include/core/instance.hpp"

using std::ifstream;
using std::cerr;
using std::endl;
using std::cout;

Instance::Instance(const std::string& filename) {
    ifstream instanceFile(filename);

    if (!instanceFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    int numJobs, numMachines;
    instanceFile >> numJobs >> numMachines; // Read the number of jobs and machines

    if (numJobs > 255 || numMachines > 255) {
        // If the number of jobs or machines is above 255, we cannot use uint8_t, so we throw an exception
        // we know that the number of jobs and machines will be below 255 in the instances we are using
        throw std::runtime_error("The number of jobs and machines must be below 255");
    }

    jobs = static_cast<uint8_t>(numJobs);
    machines = static_cast<uint8_t>(numMachines);

    processingTimes.resize(jobs, vector<uint8_t>(machines));

    // Read the processing times for each job in each machine
    for (int i = 0; i < jobs; ++i) {
        for (int j = 0; j < machines; ++j) {
            int machineNumber, processingTime;
            instanceFile >> machineNumber >> processingTime;
            // Here again we know that the processing times will be below 255 because we checked every processing time in the data analysis phase (@see dataAnalysis.hpp in the include/utils folder)
            processingTimes[i][j] = static_cast<uint8_t>(processingTime);
        }
    }
    instanceFile.close();
}

ostream& operator<<(ostream& os, const Instance& instance) {
    os << "Jobs: " << static_cast<int>(instance.jobs) << endl;
    os << "Machines: " << static_cast<int>(instance.machines) << endl;
    os << "Processing times:" << endl;
    for (int i = 0; i < instance.jobs; ++i) {
        os << "Job " << i << ": ";
        for (int j = 0; j < instance.machines; ++j) {
            os << static_cast<int>(instance.processingTimes[i][j]) << " ";
        }
        os << endl;
    }
    return os;
}