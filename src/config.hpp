//
// Created by oscar on 09/03/2025.
//

#ifndef FLOWSHOPSLS_CONFIG_HPP
#define FLOWSHOPSLS_CONFIG_HPP

#include <string>
using std::string;

/**
 * @namespace config
 * @brief Namespace that contains configuration variables
 */
namespace config {

    constexpr uint32_t seed = 42;                               // Seed for the random number generator

    inline const string projectRoot = PROJECT_SOURCE_DIR;                   // Path to the project root
    const string instancePath = projectRoot + "/instances/Benchmarks/";     // Path to the instances
}

#endif //FLOWSHOPSLS_CONFIG_HPP
