//
// Created by oscar on 09/03/2025.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include "include/dataAnalysis.hpp"

using namespace std;

/**
 * @brief Check if the processing times of a file are below 255. This function was used to check if we could use uint8_t to store the processing times
 * @param filename Path to the file
 * @return True if all the processing times are below 255, false otherwise
 */
bool checkProcessingTimes(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return false;
    }

    int numJobs, numMachines;
    file >> numJobs >> numMachines;     // Read the number of jobs and machines

    // Read all the processing times and check if they are below 255
    for (int i = 0; i < numJobs; ++i) {
        for (int j = 0; j < numMachines; ++j) {
            int machineNumber, processingTime;
            file >> machineNumber >> processingTime;
            if (processingTime > 255) {
                file.close();
                return false;
            }
        }
    }

    file.close();
    return true;
}

/**
 * @brief Check if the processing times of all the files in a directory are below 255
 * @param directory Path to the directory
 * @return True if all the processing times are below 255, false otherwise
 */
bool checkAllProcessingTimes(const string& directory) {
    for (const auto& entry : filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            if (!checkProcessingTimes(entry.path().string())) {
                return false;
            }
        }
    }
    return true;
}

