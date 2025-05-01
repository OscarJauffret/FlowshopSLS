//
// Created by oscar on 02/04/2025.
//

#ifndef PFSP_II_RUNLOGGER_HPP
#define PFSP_II_RUNLOGGER_HPP

#include <unordered_map>
#include <string>
#include "../config/flowShopConfig.hpp"
#include "stringify.hpp"

using std::unordered_map;
using std::string;

class RunLogger {
protected:
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
     * @brief Destructor for the RunLogger (inheritance)
     */
    virtual ~RunLogger() = default;

    /**
    * @brief Log the results of a run to the results file.
    * @param config The configuration of the flow shop algorithm.
    * @param nJobs The number of jobs in the instance.
    * @param time The time taken to find the solution in milliseconds.
    * @param solution The solution found.
    */
    virtual void log(const FlowShopConfig &config, uint8_t nJobs,
                     double time, const Solution &solution) const = 0;

};

class RunLoggerII final : public RunLogger {
public:
    void log(const FlowShopConfig &config, uint8_t nJobs,
             double time, const Solution &solution) const override;
};

class RunLoggerVND final : public RunLogger {
public:
    void log(const FlowShopConfig &config, uint8_t nJobs,
             double time, const Solution &solution) const override;
};

class RunLoggerMemetic final : public RunLogger {
public:
    void log(const FlowShopConfig &config, uint8_t nJobs,
             double time, const Solution &solution) const override;
};


#endif //PFSP_II_RUNLOGGER_HPP
