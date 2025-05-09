//
// Created by oscar on 07/03/2025.
//

#include <iostream>
#include <random>
#include <chrono>

#include "../include/core/instance.hpp"
#include "../include/utils/runLogger.hpp"
#include "../include/utils/factories.hpp"

using std::cout;
using std::endl;
using std::cerr;
using Clock = std::chrono::high_resolution_clock;

/**
 * @brief Main function of the program. It runs the Flow Shop Scheduling Problem algorithm.
 */
int main(int argc, char* argv[]) {
    try {
        std::random_device rd;
        std::mt19937 rng(rd());

        auto config = parseConfig(argc, argv);
        Instance instance(config->getInstancePath());

        auto start = Clock::now();
        auto solver = createSolver(*config, instance, rng);
        Solution solution = solver->run();
        auto end = Clock::now();

        double elapsed = std::chrono::duration<double, std::milli>(end - start).count();

        // For me, to control the logging of the results
        bool log = true;
        if (log) {
            auto analyzer = RunLogger();
            double pctDev = analyzer.getPercentDeviation(config->getInstancePath(), solution.getFitness());
            analyzer.log(*config, pctDev, elapsed, solution, instance.jobs);
            cout << pctDev << endl;     // This is for irace
        } else {
            cout << "Instance: " << config->getInstancePath() << endl;
            cout << "Number of jobs: " << (int) instance.jobs << endl;
            cout << solution << endl;
            cout << "Time: " << elapsed << " ms" << endl;
        }

    } catch (const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}