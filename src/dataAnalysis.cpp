//
// Created by oscar on 09/03/2025.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include "dataAnalysis.hpp"

using namespace std;


bool checkProcessingTimes(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return false;
    }

    int numJobs, numMachines;
    file >> numJobs >> numMachines;     // Read the number of jobs and machines

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

