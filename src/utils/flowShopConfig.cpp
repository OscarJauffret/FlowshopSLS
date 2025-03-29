//
// Created by oscar on 29/03/2025.
//

#include "../../include/utils/flowShopConfig.hpp"

using std::invalid_argument;

FlowShopConfig::FlowShopConfig(int argc, char* argv[]) {
    if (argc != 4) {
        throw invalid_argument("Usage: pfsp-ii (--first|--best) (--transpose|--exchange|--insert) (--srz|--random-init)");
    }

    string pivotArg = argv[1];
    if (pivotArg == "--first")
        pivotRule = PivotingRule::FIRST_IMPROVEMENT;
    else if (pivotArg == "--best")
        pivotRule = PivotingRule::BEST_IMPROVEMENT;
    else
        throw invalid_argument("Invalid pivot rule! Use --first or --best.");

    string neighborhoodArg = argv[2];
    if (neighborhoodArg == "--transpose")
        neighbourhood = NeighbourhoodStructure::TRANSPOSE;
    else if (neighborhoodArg == "--exchange")
        neighbourhood = NeighbourhoodStructure::EXCHANGE;
    else if (neighborhoodArg == "--insert")
        neighbourhood = NeighbourhoodStructure::INSERT;
    else
        throw invalid_argument("Invalid neighborhood structure! Use --transpose, --exchange, or --insert.");

    string initArg = argv[3];
    if (initArg == "--srz")
        initMethod = InitializationMethod::SIMPLIFIED_RZ;
    else if (initArg == "--random-init")
        initMethod = InitializationMethod::RANDOM;
    else
        throw invalid_argument("Invalid initialization method! Use --srz or --random-init.");
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