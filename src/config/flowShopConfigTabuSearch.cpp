//
// Created by oscar on 06/05/2025.
//

#include "../../include/config/flowShopConfigTabuSearch.hpp"
#include <iostream>

using std::cerr;
using std::endl;
using std::invalid_argument;

FlowShopConfigTabuSearch::FlowShopConfigTabuSearch(int argc, char **argv) : FlowShopConfig(argc, argv) {
    // If the algorithm type is Tabu Search, the following arguments are expected:
    // <tenure> <alpha> <max-generations> <max-stuck>
    if (argc != 7) {
        cerr << "Invalid number of arguments for Tabu Search!" << endl;
        throw invalid_argument("Usage: ./pfsp --tabu --instance <tenure> <alpha> <max-generations> <max-stuck>");
    }

    // The third argument is the tabu tenure
    tabuTenure = std::stoi(argv[3]);
    if (tabuTenure <= 0) {
        throw invalid_argument("Invalid tabu tenure! Use a positive integer.");
    }

    // The fourth argument is the alpha parameter
    alpha = std::stoi(argv[4]);
    if (alpha < -1) {
        throw invalid_argument("Invalid alpha parameter! Use a positive integer or -1 to explore the whole neighborhood.");
    }

    // The fifth argument is the maximum number of generations
    maxGenerations = std::stoi(argv[5]);
    if (maxGenerations < 0) {
        throw invalid_argument("Invalid maximum number of generations! Use a positive integer or zero to have the limit set by the VND times");
    }

    // The sixth argument is the maximum number of generations without improvement
    maxStuck = std::stoi(argv[6]);
    if (maxStuck < 0 || (maxStuck > maxGenerations && maxGenerations != 0)) {
        throw invalid_argument("Invalid maximum number of generations without improvement! Use a positive integer less than the maximum number of generations.");
    }
}

int FlowShopConfigTabuSearch::getTabuTenure() const {
    return tabuTenure;
}

int FlowShopConfigTabuSearch::getAlpha() const {
    return alpha;
}

int FlowShopConfigTabuSearch::getMaxGenerations() const {
    return maxGenerations;
}

int FlowShopConfigTabuSearch::getMaxStuck() const {
    return maxStuck;
}
