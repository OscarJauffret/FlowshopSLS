//
// Created by oscar on 29/03/2025.
//

#include "../../include/utils/flowShopConfig.hpp"
#include "../config.hpp"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

using std::cerr;
using std::endl;
using std::invalid_argument;

FlowShopConfig::FlowShopConfig(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Invalid number of arguments!" << endl;
        throw invalid_argument("Usage: ./pfsp-ii --instance --first|--best --transpose|--exchange|--insert --srz|--random-init");
    }

    // Parse the arguments
    // The first argument is the instance path
    instancePath = argv[1];
    if (instancePath.rfind("--", 0) == 0) {
        instancePath = instancePath.substr(2);
    }
    fs::path path = fs::path(config::instancePath) / instancePath;
    if (!fs::exists(path)) {
        throw invalid_argument("Instance file not found: " + path.string());
    }
    instancePath = path.string();

    // The second argument is the pivoting rule
    string pivotArg = argv[2];
    if (pivotArg == "--first") {
        pivotRule = PivotingRule::FIRST_IMPROVEMENT;
    } else if (pivotArg == "--best") {
        pivotRule = PivotingRule::BEST_IMPROVEMENT;
    } else {
        throw invalid_argument("Invalid pivoting rule! Use --first or --best.");
    }

    // The third argument is the neighbourhood structure
    string neighborhoodArg = argv[3];
    if (neighborhoodArg == "--transpose") {
        neighbourhood = NeighbourhoodStructure::TRANSPOSE;
    } else if (neighborhoodArg == "--exchange") {
        neighbourhood = NeighbourhoodStructure::EXCHANGE;
    } else if (neighborhoodArg == "--insert") {
        neighbourhood = NeighbourhoodStructure::INSERT;
    } else {
        throw invalid_argument("Invalid neighbourhood structure! Use --transpose, --exchange or --insert.");
    }

    // The fourth argument is the initialization method
    string initArg = argv[4];
    if (initArg == "--srz") {
        initMethod = InitializationMethod::SIMPLIFIED_RZ;
    } else if (initArg == "--random-init") {
        initMethod = InitializationMethod::RANDOM;
    } else {
        throw invalid_argument("Invalid initialization method! Use --srz or --random-init.");
    }

}

string FlowShopConfig::getInstancePath() const {
    return instancePath;
}

PivotingRule FlowShopConfig::getPivotRule() const {
    return pivotRule;
}

NeighbourhoodStructure FlowShopConfig::getNeighbourhood() const {
    return neighbourhood;
}

InitializationMethod FlowShopConfig::getInitMethod() const {
    return initMethod;
}
