//
// Created by oscar on 02/04/2025.
//

#include "../../include/utils/runAnalyzer.hpp"
#include "../config.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using std::getline;

RunAnalyzer::RunAnalyzer() {
    loadBestKnown();
}

void RunAnalyzer::loadBestKnown() {
    std::ifstream file(config::bestKnownPath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open best-known file: " + config::bestKnownPath);
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        std::istringstream ss(line);
        string instanceName, valueStr;

        getline(ss, instanceName, ',');
        getline(ss, valueStr);

        // Clean whitespace
        instanceName.erase(remove_if(instanceName.begin(), instanceName.end(), isspace), instanceName.end());
        valueStr.erase(remove_if(valueStr.begin(), valueStr.end(), isspace), valueStr.end());

        bestKnown[instanceName] = std::stoull(valueStr);
    }

}

double RunAnalyzer::getPercentDeviation(const string &instancePath, uint64_t value) const {
    auto it = bestKnown.find(getInstanceName(instancePath));
    if (it == bestKnown.end()) {
        // No best known solution for this instance
        return 0.0;
    }

    return (value - it->second) / static_cast<double>(it->second) * 100.0;
}

string RunAnalyzer::getInstanceName(const string &fullpath) {
    return fs::path(fullpath).filename().string();
}

void RunAnalyzer::logII(const string &instancePath, uint8_t nJobs, const PivotingRule &rule,
                        const NeighbourhoodStructure &neighbourhood, const InitializationMethod &initMethod,
                        double time_ms, const Solution &solution) const {

    uint64_t fitness = solution.getFitness();
    double pctDev = getPercentDeviation(instancePath, fitness);

    std::ofstream file(config::resultsPathII, std::ios_base::app);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open results file: " + config::resultsPathII);
    }
    file << getInstanceName(instancePath) << ","
         << static_cast<int>(nJobs) << ","
         << fitness << ","
         << pctDev << ","
         << stringify::pivot(rule) << ","
         << stringify::neighbourhood(neighbourhood) << ","
         << stringify::init(initMethod) << ","
         << time_ms
         << std::endl;
}

void RunAnalyzer::logVND(const string &instancePath, uint8_t nJobs, const VNDStrategy &vndStrategy, double time_ms,
                         const Solution &solution) const {

    uint64_t fitness = solution.getFitness();
    double pctDev = getPercentDeviation(instancePath, fitness);

    std::ofstream file(config::resultsPathVND, std::ios_base::app);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open results file: " + config::resultsPathVND);
    }

    file << getInstanceName(instancePath) << ","
         << static_cast<int>(nJobs) << ","
         << fitness << ","
         << pctDev << ","
         << stringify::vnd(vndStrategy) << ","
         << time_ms
         << std::endl;

}
