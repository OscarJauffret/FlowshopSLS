//
// Created by oscar on 29/03/2025.
//

#include "../../include/config/flowShopConfig.hpp"
#include "../config.hpp"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

using std::cerr;
using std::endl;
using std::invalid_argument;

FlowShopConfig::FlowShopConfig(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Invalid number of arguments!" << endl;
        throw invalid_argument("Usage: ./pfsp --ii|--vnd|--memetic --instance <arguments>");
    }

    // Parse the arguments
    // The first argument is the algorithm type
    string algorithmArg = argv[1];
    if (algorithmArg == "--ii") {
        algorithmType = AlgorithmType::II;
    } else if (algorithmArg == "--vnd") {
        algorithmType = AlgorithmType::VND;
    } else if (algorithmArg == "--memetic") {
        algorithmType = AlgorithmType::MEMETIC;
    } else {
        throw invalid_argument("Invalid algorithm type! Use --ii, --vnd or --memetic.");
    }

    // The second argument is the instance path
    instancePath = argv[2];
    if (instancePath.rfind("--", 0) == 0) {
        instancePath = instancePath.substr(2);
    }
    fs::path path = fs::path(config::paths::instancePath) / instancePath;
    if (!fs::exists(path)) {
        throw invalid_argument("Instance file not found: " + path.string());
    }
    instancePath = path.string();
}

AlgorithmType FlowShopConfig::getAlgorithmType() const {
    return algorithmType;
}

string FlowShopConfig::getInstancePath() const {
    return instancePath;
}