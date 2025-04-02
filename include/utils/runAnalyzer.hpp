//
// Created by oscar on 02/04/2025.
//

#ifndef PFSP_II_RUNANALYZER_HPP
#define PFSP_II_RUNANALYZER_HPP

#include <unordered_map>
#include <string>
#include "flowShopConfig.hpp"
#include "stringify.hpp"

using std::unordered_map;
using std::string;

class RunAnalyzer {
    unordered_map<string, uint64_t> bestKnown;

    /**
     * @brief Load the best-known solutions from the file specified in the configuration.
     * @throws runtime_error if the file could not be opened.
     */
    void loadBestKnown();

    /**
     * @brief Get the percent deviation of the given value from the best-known solution for the given instance.
     * @param instancePath The absolute path of the instance.
     * @param value The value to compare.
     * @return The percent deviation of the given value from the best-known solution for the given instance.
     */
    [[nodiscard]] double getPercentDeviation(const string &instancePath, uint64_t value) const;

    /**
     * @brief Get the instance name from the full path.
     * @param fullpath The absolute path of the instance.
     * @return The name of the instance.
     */
    static string getInstanceName(const string &fullpath) ;

public:

    /**
     * @brief Construct a new RunAnalyzer object.
     */
    RunAnalyzer();

    /**
     * @brief Log the results of a run to the results file.
     * @param instancePath The path to the instance file.
     * @param solution The solution found.
     * @param rule The pivoting rule used.
     * @param neighbourhood The neighbourhood structure used.
     * @param initMethod The initialization method used.
     * @param time_ms The time taken to find the solution in milliseconds.
     */
    void log(const string &instancePath, const Solution &solution, const PivotingRule &rule,
             const NeighbourhoodStructure &neighbourhood, const InitializationMethod &initMethod,
             double time_ms) const;

};


#endif //PFSP_II_RUNANALYZER_HPP
