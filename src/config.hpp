//
// Created by oscar on 09/03/2025.
//

#ifndef FLOWSHOPSLS_CONFIG_HPP
#define FLOWSHOPSLS_CONFIG_HPP

#include <string>
#include <cstdint>
#include <vector>

using std::string;
using std::vector;

/**
 * @namespace config
 * @brief Namespace that contains configuration variables
 */
namespace config {
    namespace paths {
        inline const string projectRoot = PROJECT_SOURCE_DIR;                         // Path to the project root
        const string instancePath = projectRoot + "/instances/Benchmarks/";           // Path to the instances
        const string bestKnownPath = projectRoot + "/instances/bestKnownTCT.txt";     // Path to the best known solutions

        const string resultsPathII = projectRoot + "/results/resultsII.csv";                      // Path to the results
        const string resultsPathVND = projectRoot + "/results/resultsVND.csv";                    // Path to the results
        const string resultsPathMemetic = projectRoot + "/results/resultsMemetic.csv";            // Path to the results

        const string vndTimesPath = projectRoot + "/results/vnd/time_comparison.csv";             // Path to the VND times
    }

    namespace memetic {
        constexpr int getNumCuts(const int instanceSize) {
            switch (instanceSize) {
                case 50: return 15;
                case 100: return 31;
                case 200: return 59;
                default: return 10;             // Default value for other sizes (should never happen)
            }
        }

        inline vector<int> getFirstColumnOfOrthogonalArray(const int n) {
            // See R. L. Plackett and J. P. Burman
            switch (n) {
            case 16: return {1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0};
            case 32: return {0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1};
            case 60: return {1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1,
                0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0};
            default: return {0}; // Default value for other sizes (should never happen)
            }
        }

        constexpr int thresholdLocalSearch = 10;    // Threshold for the number of iterations without improvement before starting the local search
    }
}

#endif //FLOWSHOPSLS_CONFIG_HPP
