//
// Created by Oscar Jauffret on 23/04/2025.
//

#ifndef SOLVERFACTORY_HPP
#define SOLVERFACTORY_HPP

#include "../config/flowShopConfig.hpp"
#include "../config/flowShopConfigII.hpp"
#include "../config/flowShopConfigVnd.hpp"
#include "../config/flowShopConfigMemetic.hpp"
#include "../core/flowShopSolver.hpp"
#include "../core/flowShopII.hpp"
#include "../core/flowShopVnd.hpp"
#include "../core/flowShopMemetic.hpp"
#include "runLogger.hpp"

inline std::unique_ptr<FlowShopConfig> parseConfig(int argc, char* argv[]) {
    std::string algo = argv[1];
    if (algo == "--ii") {
        return std::make_unique<FlowShopConfigII>(argc, argv);
    } else if (algo == "--vnd") {
        return std::make_unique<FlowShopConfigVND>(argc, argv);
    } else if (algo == "--memetic") {
        return std::make_unique<FlowShopConfigMemetic>(argc, argv);
    } else {
        throw std::invalid_argument("Unknown algorithm type.");
    }
}

/**
* @brief The createSolver function creates a FlowShopSolver object based on the given configuration and instance.
* @param config The configuration for the Flow Shop algorithm.
* @param instance The instance to solve.
* @param rng The random number generator to use.
* @return A unique pointer to the FlowShopSolver object.
*/
inline std::unique_ptr<FlowShopSolver> createSolver(const FlowShopConfig& config, const Instance& instance, std::mt19937& rng) {
    switch (config.getAlgorithmType()) {
        case AlgorithmType::II: {
            auto& iiConfig = dynamic_cast<const FlowShopConfigII&>(config);
            return std::make_unique<FlowShopII>(instance, iiConfig.getNeighbourhood(), iiConfig.getPivotRule(),
                iiConfig.getInitMethod(), rng);
        } case AlgorithmType::VND: {
            auto& vndConfig = dynamic_cast<const FlowShopConfigVND&>(config);
            return std::make_unique<FlowShopVND>(instance, vndConfig.getVNDStrategy(), rng);
        } case AlgorithmType::MEMETIC: {
            auto& memeticConfig = dynamic_cast<const FlowShopConfigMemetic&>(config);
            return std::make_unique<FlowShopMemetic>(instance, memeticConfig.getPopulationSize(),
                memeticConfig.getMutationRate(), memeticConfig.getLocalSearchMethod(), rng);
        } default: {
            throw std::invalid_argument("Unsupported algorithm type");
        }
    }
}


#endif //SOLVERFACTORY_HPP
