//
// Created by oscar on 07/03/2025.
//

#include <iostream>
#include <random>
#include "config.hpp"
#include "../include/core/instance.hpp"
#include "../include/core/flowShopII.hpp"

using std::cout;
using std::endl;
using std::cerr;

int main(int argc, char* argv[]) {
    try {
        std::random_device rd;
        std::mt19937 rng(rd());

        FlowShopConfig config(argc, argv);

        Instance instance(config.getInstancePath());
        FlowShopII flowShopII(instance, config.getNeighbourhood(), config.getPivotRule(), config.getInitMethod(), rng);
        Solution solution = flowShopII.run();
        cout << "Best solution found: " << endl << solution << endl;
    } catch (const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}