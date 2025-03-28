//
// Created by oscar on 07/03/2025.
//

#include <iostream>
#include "config.hpp"
#include "../include/core/instance.hpp"
#include "../include/initialization/initialization.hpp"

using std::cout;
using std::endl;

int main() {
    string instancePath = config::instancePath + "ta051";
    Instance instance(instancePath);

    cout << instance << endl;

    std::mt19937 rng(config::seed);

    Solution solution = initialization::random(instance, rng);
    cout << solution << endl;

    return 0;
}