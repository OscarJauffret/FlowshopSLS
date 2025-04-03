//
// Created by oscar on 09/03/2025.
//

#ifndef FLOWSHOPSLS_CONFIG_HPP
#define FLOWSHOPSLS_CONFIG_HPP

#include <string>
#include <cstdint>
using std::string;

/**
 * @namespace config
 * @brief Namespace that contains configuration variables
 */
namespace config {

    inline const string projectRoot = PROJECT_SOURCE_DIR;                         // Path to the project root
    const string instancePath = projectRoot + "/instances/Benchmarks/";           // Path to the instances
    const string bestKnownPath = projectRoot + "/instances/bestKnownTCT.txt";     // Path to the best known solutions

    const string resultsPathII = projectRoot + "/resultsII.csv";                      // Path to the results
    const string resultsPathVND = projectRoot + "/resultsVND.csv";                    // Path to the results
}

#endif //FLOWSHOPSLS_CONFIG_HPP
