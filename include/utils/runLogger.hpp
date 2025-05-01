//
// Created by oscar on 02/04/2025.
//

#ifndef PFSP_II_RUNLOGGER_HPP
#define PFSP_II_RUNLOGGER_HPP

#include <unordered_map>
#include <string>
#include "../config/flowShopConfig.hpp"
#include "../config/flowShopConfigII.hpp"
#include "../config/flowShopConfigVnd.hpp"
#include "../config/flowShopConfigMemetic.hpp"

#include "stringify.hpp"

using std::unordered_map;
using std::string;

class RunLogger {
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
     * @brief Construct a new RunLogger object.
     */
    RunLogger();

    /**
    * @brief Log iterative improvement results of a run to the results file.
    * @param config The II configuration of the flow shop algorithm.
    * @param nJobs The number of jobs in the instance.
    * @param time The time taken to find the solution in milliseconds.
    * @param solution The solution found.
    */
    void log(const FlowShopConfigII &config, uint8_t nJobs, double time, const Solution &solution) const;

    /**
    * @brief Log VND results of a run to the results file.
    * @param config The VND configuration of the flow shop algorithm.
    * @param nJobs The number of jobs in the instance.
    * @param time The time taken to find the solution in milliseconds.
    * @param solution The solution found.
    */
    void log(const FlowShopConfigVND &config, uint8_t nJobs, double time, const Solution &solution) const;

    /**
    * @brief Log memetic results of a run to the results file.
    * @param config The memetic configuration of the flow shop algorithm.
    * @param nJobs The number of jobs in the instance.
    * @param time The time taken to find the solution in milliseconds.
    * @param solution The solution found.
    */
    void log(const FlowShopConfigMemetic &config, uint8_t nJobs, double time, const Solution &solution) const;

    /**
     * @brief Log results of a run to the results file.
     * @param config The configuration of the flow shop algorithm.
     * @param nJobs The number of jobs in the instance.
     * @param time The time taken to find the solution in milliseconds.
     * @param solution The solution found.
     */
    void log(const FlowShopConfig& config, uint8_t nJobs, double time, const Solution& solution) const;

};


#endif //PFSP_II_RUNLOGGER_HPP
