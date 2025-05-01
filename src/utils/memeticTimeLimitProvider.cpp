//
// Created by Oscar Jauffret on 01/05/2025.
//

#include "../../include/utils/memeticTimeLimitProvider.hpp"
#include "../config.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

using std::string;

std::unordered_map<int, int> MemeticTimeLimitProvider::vndTimes;
bool MemeticTimeLimitProvider::isLoaded = false;

void MemeticTimeLimitProvider::loadVNDTimes() {
    const string filename = config::paths::vndTimesPath;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    string line;
    bool firstLine = true;

    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue; // skip header
        }

        std::istringstream ss(line);
        string cmp1, cmp2, n_jobs_str, mean1_str, mean2_str;
        std::getline(ss, cmp1, ',');
        std::getline(ss, cmp2, ',');
        std::getline(ss, n_jobs_str, ',');
        std::getline(ss, mean1_str, ',');
        std::getline(ss, mean2_str, ',');

        int size = std::stoi(n_jobs_str);
        double mean1 = std::stod(mean1_str);
        double mean2 = std::stod(mean2_str);
        int averageTime = static_cast<int>((mean1 + mean2) / 2.0);

        vndTimes[size] = averageTime;
    }

    isLoaded = true;
}

int MemeticTimeLimitProvider::getMemeticAllowedTime(const int instanceSize) {
    if (!isLoaded) {
        loadVNDTimes();
    }

    auto it = vndTimes.find(instanceSize);
    if (it == vndTimes.end()) {
        throw std::runtime_error("Instance size not found in VND times.");
    }

    int multiplier;
    switch (instanceSize) {
        case 50:
        case 100:
            multiplier = 500;
            break;
        case 200:
            multiplier = 100;
            break;
        default:
            throw std::runtime_error("Invalid instance size");
    }

    return it->second * multiplier;

}