//
// Created by oscar on 07/03/2025.
//

#include <iostream>
#include <random>
#include <chrono>

#include "config.hpp"
#include "../include/core/instance.hpp"
#include "../include/core/flowShopII.hpp"
#include "../include/utils/runAnalyzer.hpp"

using std::cout;
using std::endl;
using std::cerr;
using Clock = std::chrono::high_resolution_clock;

int main(int argc, char* argv[]) {
    try {
        std::random_device rd;
        std::mt19937 rng(rd());

        FlowShopConfig config(argc, argv);

        auto start = Clock::now();
        Instance instance(config.getInstancePath());
        FlowShopII flowShopII(instance, config.getNeighbourhood(), config.getPivotRule(), config.getInitMethod(), rng);
        Solution solution = flowShopII.run();
        auto end = Clock::now();
        double elapsed = std::chrono::duration<double, std::milli>(end - start).count();

        RunAnalyzer analyzer;
        analyzer.log(config.getInstancePath(), instance.jobs, config.getPivotRule(),
                     config.getNeighbourhood(), config.getInitMethod(), elapsed, solution);
    } catch (const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}