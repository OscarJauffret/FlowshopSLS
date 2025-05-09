//
// Created by oscar on 02/04/2025.
//

#include "../../include/utils/runLogger.hpp"
#include "../config.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using std::getline;

RunLogger::RunLogger() {
    loadBestKnown();
}

void RunLogger::loadBestKnown() {
    std::ifstream file(config::paths::bestKnownPath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open best-known file: " + config::paths::bestKnownPath);
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

double RunLogger::getPercentDeviation(const string &instancePath, uint64_t value) const {
    auto it = bestKnown.find(getInstanceName(instancePath));
    if (it == bestKnown.end()) {
        // No best known solution for this instance
        return 0.0;
    }

    return (value - it->second) / static_cast<double>(it->second) * 100.0;
}

string RunLogger::getInstanceName(const string &fullpath) {
    return fs::path(fullpath).filename().string();
}

void RunLogger::log(const FlowShopConfigII &config, const uint8_t nJobs,
                      const double time, const Solution &solution) const {

    uint64_t fitness = solution.getFitness();
    string instancePath = config.getInstancePath();
    double pctDev = getPercentDeviation(instancePath, fitness);

    std::ofstream file(config::paths::resultsPathII, std::ios_base::app);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open results file: " + config::paths::resultsPathII);
    }
    file << getInstanceName(instancePath) << ","
         << static_cast<int>(nJobs) << ","
         << fitness << ","
         << pctDev << ","
         << stringify::pivot(config.getPivotRule()) << ","
         << stringify::neighbourhood(config.getNeighbourhood()) << ","
         << stringify::init(config.getInitMethod()) << ","
         << time
         << std::endl;
}

void RunLogger::log(const FlowShopConfigVND &config, const uint8_t nJobs,
                       const double time, const Solution &solution) const {

    uint64_t fitness = solution.getFitness();
    string instancePath = config.getInstancePath();
    double pctDev = getPercentDeviation(instancePath, fitness);

    std::ofstream file(config::paths::resultsPathVND, std::ios_base::app);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open results file: " + config::paths::resultsPathVND);
    }

    file << getInstanceName(instancePath) << ","
         << static_cast<int>(nJobs) << ","
         << fitness << ","
         << pctDev << ","
         << stringify::vnd(config.getVNDStrategy()) << ","
         << time
         << std::endl;

}

void RunLogger::log(const FlowShopConfigMemetic &config, const uint8_t nJobs,
                    const double time, const Solution &solution) const {

    uint64_t fitness = solution.getFitness();
    string instancePath = config.getInstancePath();
    double pctDev = getPercentDeviation(instancePath, fitness);

    std::ofstream file(config::paths::resultsPathMemetic, std::ios_base::app);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open results file: " + config::paths::resultsPathMemetic);
    }

    file << getInstanceName(instancePath) << ","
         << static_cast<int>(nJobs) << ","
         << fitness << ","
         << pctDev << ","
         << config.getPopulationSize() << ","
         << time
         << std::endl;
}

void RunLogger::log(const FlowShopConfigTabuSearch &config, uint8_t nJobs,
                    double time, const Solution &solution) const {
    uint64_t fitness = solution.getFitness();
    string instancePath = config.getInstancePath();
    double pctDev = getPercentDeviation(instancePath, fitness);

    std::ofstream file(config::paths::resultsPathTabu, std::ios_base::app);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open results file: " + config::paths::resultsPathTabu);
    }

    file << getInstanceName(instancePath) << ","
         << static_cast<int>(nJobs) << ","
         << fitness << ","
         << pctDev << ","
         << config.getTabuTenure() << ","
         << config.getAlpha() << ","
         << config.getMaxGenerations() << ","
         << config.getMaxStuck() << ","
         << time
         << std::endl;

}

void RunLogger::log(const FlowShopConfig& config, const uint8_t nJobs,
                    const double time, const Solution& solution) const {
    switch (config.getAlgorithmType()) {
    case AlgorithmType::II:
        log(dynamic_cast<const FlowShopConfigII&>(config), nJobs, time, solution);
        break;
    case AlgorithmType::VND:
        log(dynamic_cast<const FlowShopConfigVND&>(config), nJobs, time, solution);
        break;
    case AlgorithmType::MEMETIC:
        log(dynamic_cast<const FlowShopConfigMemetic&>(config), nJobs, time, solution);
        break;
    case AlgorithmType::TABU_SEARCH:
        log(dynamic_cast<const FlowShopConfigTabuSearch&>(config), nJobs, time, solution);
        break;
    default:
        throw std::invalid_argument("Unknown algorithm type in logger.");
    }
}
