//
// Created by Oscar Jauffret on 23/04/2025.
//

#ifndef SOLVERFACTORY_HPP
#define SOLVERFACTORY_HPP

#include "flowShopConfig.hpp"
#include "../core/flowShopSolver.hpp"
#include "../core/flowShopII.hpp"
#include "../core/flowShopVnd.hpp"
#include "../core/flowShopMemetic.hpp"
#include "runLogger.hpp"

/**
* @brief The createSolver function creates a FlowShopSolver object based on the given configuration and instance.
* @param config The configuration for the Flow Shop algorithm.
* @param instance The instance to solve.
* @param rng The random number generator to use.
* @return A unique pointer to the FlowShopSolver object.
*/
inline std::unique_ptr<FlowShopSolver> createSolver(const FlowShopConfig& config, const Instance& instance, std::mt19937& rng) {
    switch (config.getAlgorithmType()) {
    case AlgorithmType::II:
        return std::make_unique<FlowShopII>(instance, config.getNeighbourhood(), config.getPivotRule(), config.getInitMethod(), rng);
    case AlgorithmType::VND:
        return std::make_unique<FlowShopVND>(instance, config.getVNDStrategy(), rng);
    case AlgorithmType::MEMETIC:
        return std::make_unique<FlowShopMemetic>(instance, config.getPopulationSize(), rng);
    default:
        throw std::invalid_argument("Unsupported algorithm type");
    }
}

/**
* @brief The createRunLogger function creates a RunLogger object based on the given configuration.
* @param config The configuration for the Flow Shop algorithm.
* @return A unique pointer to the RunLogger object.
*/
inline std::unique_ptr<RunLogger> createRunLogger(const FlowShopConfig& config) {
    switch (config.getAlgorithmType()) {
    case AlgorithmType::II:
        return std::make_unique<RunLoggerII>();
    case AlgorithmType::VND:
        return std::make_unique<RunLoggerVND>();
    case AlgorithmType::MEMETIC:
        return std::make_unique<RunLoggerMemetic>();
    default:
        throw std::invalid_argument("Unsupported algorithm type");
    }
}



#endif //SOLVERFACTORY_HPP
