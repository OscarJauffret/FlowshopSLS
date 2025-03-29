//
// Created by oscar on 29/03/2025.
//

#include "../../include/utils/flowShopConfig.hpp"

#include <iostream>

using std::cerr;
using std::endl;
using std::invalid_argument;

FlowShopConfig::FlowShopConfig(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Invalid number of arguments!" << endl;
        throw invalid_argument("Usage: ./pfsp-ii --first|--best --transpose|--exchange|--insert --srz|--random-init");
    }

    // Parse the arguments

    // The first argument is the pivoting rule
    string pivotArg = argv[1];
    if (pivotArg == "--first") {
        pivotRule = PivotingRule::FIRST_IMPROVEMENT;
    } else if (pivotArg == "--best") {
        pivotRule = PivotingRule::BEST_IMPROVEMENT;
    } else {
        throw invalid_argument("Invalid pivoting rule! Use --first or --best.");
    }

    // The second argument is the neighbourhood structure
    string neighborhoodArg = argv[2];
    if (neighborhoodArg == "--transpose") {
        neighbourhood = NeighbourhoodStructure::TRANSPOSE;
    } else if (neighborhoodArg == "--exchange") {
        neighbourhood = NeighbourhoodStructure::EXCHANGE;
    } else if (neighborhoodArg == "--insert") {
        neighbourhood = NeighbourhoodStructure::INSERT;
    } else {
        throw invalid_argument("Invalid neighbourhood structure! Use --transpose, --exchange or --insert.");
    }

    // The third argument is the initialization method
    string initArg = argv[3];
    if (initArg == "--srz") {
        initMethod = InitializationMethod::SIMPLIFIED_RZ;
    } else if (initArg == "--random-init") {
        initMethod = InitializationMethod::RANDOM;
    } else {
        throw invalid_argument("Invalid initialization method! Use --srz or --random-init.");
    }

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