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
    if (argc != 6 and argc != 4) {
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

    switch (getAlgorithmType()) {
        case AlgorithmType::II:
            parseArgumentsII(argc, argv);
            break;
        case AlgorithmType::VND:
            parseArgumentsVND(argc, argv);
            break;
        case AlgorithmType::MEMETIC:
            parseArgumentsMemetic(argc, argv);
            break;
        default:
            throw invalid_argument("Invalid algorithm type!");
    }
}

void FlowShopConfig::parseArgumentsII(int argc, char* argv[]) {
    // If the algorithm type is II, the following arguments are expected:
    // --pivoting-rule --neighbourhood --initialization-method
    if (argc != 6) {
        cerr << "Invalid number of arguments for II!" << endl;
        throw invalid_argument("Usage: ./pfsp --ii --instance --first|--best --transpose|--exchange|--insert --srz|--random-init");
    }

    // The third argument is the pivoting rule
    string pivotArg = argv[3];
    if (pivotArg == "--first") {
        pivotRule = PivotingRule::FIRST_IMPROVEMENT;
    } else if (pivotArg == "--best") {
        pivotRule = PivotingRule::BEST_IMPROVEMENT;
    } else {
        throw invalid_argument("Invalid pivoting rule! Use --first or --best.");
    }

    // The fourth argument is the neighbourhood structure
    string neighborhoodArg = argv[4];
    if (neighborhoodArg == "--transpose") {
        neighbourhood = NeighbourhoodStructure::TRANSPOSE;
    } else if (neighborhoodArg == "--exchange") {
        neighbourhood = NeighbourhoodStructure::EXCHANGE;
    } else if (neighborhoodArg == "--insert") {
        neighbourhood = NeighbourhoodStructure::INSERT;
    } else {
        throw invalid_argument("Invalid neighbourhood structure! Use --transpose, --exchange or --insert.");
    }

    // The fifth argument is the initialization method
    string initArg = argv[5];
    if (initArg == "--srz") {
        initMethod = InitializationMethod::SIMPLIFIED_RZ;
    } else if (initArg == "--random-init") {
        initMethod = InitializationMethod::RANDOM;
    } else {
        throw invalid_argument("Invalid initialization method! Use --srz or --random-init.");
    }
}

void FlowShopConfig::parseArgumentsVND(int argc, char* argv[]) {
    // If the algorithm type is VND, the only argument is the VND strategy
    // The third argument is the VND strategy
    if (argc != 4) {
        cerr << "Invalid number of arguments for VND!" << endl;
        throw invalid_argument("Usage: ./pfsp --vnd --instance --tei|--tie");
    }

    string vndArg = argv[3];
    if (vndArg == "--tei") {
        vndStrategy = VNDStrategy::TEI;
    } else if (vndArg == "--tie") {
        vndStrategy = VNDStrategy::TIE;
    } else {
        throw invalid_argument("Invalid VND strategy! Use --tei or --tie.");
    }

}

void FlowShopConfig::parseArgumentsMemetic(int argc, char* argv[]) {
    // If the algorithm type is MEMETIC, the only argument is the population size
    if (argc != 4) {
        cerr << "Invalid number of arguments for MEMETIC!" << endl;
        throw invalid_argument("Usage: ./pfsp --memetic --instance <population-size>");
    }

    // The third argument is the population size
    populationSize = std::stoi(argv[3]);
    if (populationSize <= 0) {
        throw invalid_argument("Invalid population size! Use a positive integer.");
    }
}

AlgorithmType FlowShopConfig::getAlgorithmType() const {
    return algorithmType;
}

string FlowShopConfig::getInstancePath() const {
    return instancePath;
}

PivotingRule FlowShopConfig::getPivotRule() const {
    if (algorithmType != AlgorithmType::II) {
        throw invalid_argument("Pivoting rule is only applicable for II!");
    }
    return pivotRule;
}

NeighbourhoodStructure FlowShopConfig::getNeighbourhood() const {
    if (algorithmType != AlgorithmType::II) {
        throw invalid_argument("Neighbourhood structure is only applicable for II!");
    }
    return neighbourhood;
}

InitializationMethod FlowShopConfig::getInitMethod() const {
    if (algorithmType != AlgorithmType::II) {
        throw invalid_argument("Initialization method is only applicable for II!");
    }
    return initMethod;
}

VNDStrategy FlowShopConfig::getVNDStrategy() const {
    if (algorithmType != AlgorithmType::VND) {
        throw invalid_argument("VND strategy is only applicable for VND!");
    }
    return vndStrategy;
}

int FlowShopConfig::getPopulationSize() const {
    if (algorithmType != AlgorithmType::MEMETIC) {
        throw invalid_argument("Population size is only applicable for MEMETIC!");
    }
    return populationSize;
}
