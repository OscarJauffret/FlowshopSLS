//
// Created by oscar on 07/03/2025.
//

#include <iostream>
#include "config.hpp"
#include "../include/core/instance.hpp"
#include "../include/core/flowShopII.hpp"
#include "../include/utils/flowShopConfig.hpp"

using std::cout;
using std::endl;
using std::cerr;

int main(int argc, char* argv[]) {
    try {
        string instancePath = config::instancePath + "ta051";
        Instance instance(instancePath);
        std::mt19937 rng(config::seed);

        FlowShopConfig config(argc, argv);

        FlowShopII flowShopII(instance, config.getNeighbourhood(), config.getPivotRule(), config.getInitMethod(), rng);
        flowShopII.run();
    } catch (const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}