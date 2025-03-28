//
// Created by oscar on 07/03/2025.
//

#include <iostream>
#include "config.hpp"
#include "../include/core/instance.hpp"
#include "../include/core/flowShopII.hpp"

using std::cout;
using std::endl;

int main() {
    string instancePath = config::instancePath + "ta051";
    Instance instance(instancePath);
    std::mt19937 rng(config::seed);

    FlowShopII flowShopII(instance, NeighbourhoodStructure::INSERT, PivotingRule::FIRST_IMPROVEMENT, InitializationMethod::RANDOM, rng);
    flowShopII.run();
//    Solution sol = initialization::random(instance, rng);
//    cout << sol << endl;
//    Solution newSol = sol.insert(0, sol.getNumberOfJobs()-1);
//    cout << newSol << endl;
    return 0;
}