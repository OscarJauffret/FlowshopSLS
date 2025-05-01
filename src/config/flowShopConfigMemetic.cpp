//
// Created by Oscar Jauffret on 01/05/2025.
//

#include "../../include/config/flowShopConfigMemetic.hpp"

#include <iostream>

using std::cerr;
using std::endl;
using std::invalid_argument;

FlowShopConfigMemetic::FlowShopConfigMemetic(int argc, char* argv[]): FlowShopConfig(argc, argv) {
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

int FlowShopConfigMemetic::getPopulationSize() const {
    return populationSize;
}
