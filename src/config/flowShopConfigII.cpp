//
// Created by Oscar Jauffret on 01/05/2025.
//

#include "../../include/config/flowShopConfigII.hpp"

#include <iostream>

using std::cerr;
using std::endl;
using std::invalid_argument;

FlowShopConfigII::FlowShopConfigII(int argc, char* argv[]): FlowShopConfig(argc, argv) {
    // If the algorithm type is II, the following arguments are expected:
    // --pivoting-rule --neighbourhood --initialization-method
    if (argc != 6) {
        cerr << "Invalid number of arguments for II!" << endl;
        throw invalid_argument(
            "Usage: ./pfsp --ii --instance --first|--best --transpose|--exchange|--insert --srz|--random-init");
    }

    // The third argument is the pivoting rule
    string pivotArg = argv[3];
    if (pivotArg == "--first") {
        pivotRule = PivotingRule::FIRST_IMPROVEMENT;
    }
    else if (pivotArg == "--best") {
        pivotRule = PivotingRule::BEST_IMPROVEMENT;
    }
    else {
        throw invalid_argument("Invalid pivoting rule! Use --first or --best.");
    }

    // The fourth argument is the neighbourhood structure
    string neighborhoodArg = argv[4];
    if (neighborhoodArg == "--transpose") {
        neighbourhood = NeighbourhoodStructure::TRANSPOSE;
    }
    else if (neighborhoodArg == "--exchange") {
        neighbourhood = NeighbourhoodStructure::EXCHANGE;
    }
    else if (neighborhoodArg == "--insert") {
        neighbourhood = NeighbourhoodStructure::INSERT;
    }
    else {
        throw invalid_argument("Invalid neighbourhood structure! Use --transpose, --exchange or --insert.");
    }

    // The fifth argument is the initialization method
    string initArg = argv[5];
    if (initArg == "--srz") {
        initMethod = InitializationMethod::SIMPLIFIED_RZ;
    }
    else if (initArg == "--random-init") {
        initMethod = InitializationMethod::RANDOM;
    }
    else {
        throw invalid_argument("Invalid initialization method! Use --srz or --random-init.");
    }
}

PivotingRule FlowShopConfigII::getPivotRule() const {
    return pivotRule;
}

NeighbourhoodStructure FlowShopConfigII::getNeighbourhood() const {
    return neighbourhood;
}

InitializationMethod FlowShopConfigII::getInitMethod() const {
    return initMethod;
}