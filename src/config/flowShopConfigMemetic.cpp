//
// Created by Oscar Jauffret on 01/05/2025.
//

#include "../../include/config/flowShopConfigMemetic.hpp"

#include <iostream>

using std::cerr;
using std::endl;
using std::invalid_argument;

FlowShopConfigMemetic::FlowShopConfigMemetic(int argc, char* argv[]): FlowShopConfig(argc, argv) {
    // If the algorithm type is MEMETIC, the following arguments are expected:
    // <population size> --local-search
    if (argc != 5) {
        cerr << "Invalid number of arguments for MEMETIC!" << endl;
        throw invalid_argument("Usage: ./pfsp --memetic --instance <population-size> --none|--ii|--vnd");
    }

    // The third argument is the population size
    populationSize = std::stoi(argv[3]);
    if (populationSize <= 0) {
        throw invalid_argument("Invalid population size! Use a positive integer.");
    }

    // The fourth argument is the local search method
    string localSearchArg = argv[4];
    if (localSearchArg == "--ii") {
        localSearchMethod = LocalSearchMethod::II;
    } else if (localSearchArg == "--vnd") {
        localSearchMethod = LocalSearchMethod::VND;
    } else if (localSearchArg == "--none") {
        localSearchMethod = LocalSearchMethod::NONE;
    } else {
        throw invalid_argument("Invalid local search method! Use --none, --ii or --vnd.");
    }

}

int FlowShopConfigMemetic::getPopulationSize() const {
    return populationSize;
}

LocalSearchMethod FlowShopConfigMemetic::getLocalSearchMethod() const {
    return localSearchMethod;
}
