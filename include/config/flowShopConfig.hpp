//
// Created by oscar on 29/03/2025.
//


/**
 * @file flowShopConfig.hpp
 * @brief Contains the enumeration types and the FlowShopConfig class,
 *        which parses and stores the command-line configuration parameters
 *        used to control the behavior of the Flow Shop algorithm.
 */

#ifndef FLOWSHOPSLS_FLOWSHOPCONFIG_HPP
#define FLOWSHOPSLS_FLOWSHOPCONFIG_HPP

#include <string>
#include "../neighbourhoods/neighbourhoodIterator.hpp"
#include "../initialization/initialization.hpp"


/**
 * @enum InitializationMethod
 * @brief Enumeration type that defines the initialization methods available for the Flow Shop algorithm.
 */
enum class InitializationMethod {
    RANDOM,
    SIMPLIFIED_RZ
};

/**
 * @enum NeighbourhoodStructure
 * @brief Enumeration type that defines the neighbourhood structures available for the Flow Shop algorithm.
 */
enum class NeighbourhoodStructure {
    TRANSPOSE,
    EXCHANGE,
    INSERT
};

/**
 * @enum PivotingRule
 * @brief Enumeration type that defines the pivoting rules available for the Flow Shop algorithm.
 */
enum class PivotingRule {
    FIRST_IMPROVEMENT,
    BEST_IMPROVEMENT
};

/**
 * @enum VNDStrategy
 * @brief Enumeration type that defines the VND strategies available for the Flow Shop algorithm.
 */
enum class VNDStrategy {
    TEI,        // Transpose -> Exchange -> Insert
    TIE,        // Transpose -> Insert -> Exchange
};

/**
 * @enum AlgorithmType
 * @brief Enumeration type that defines the algorithm types available for the Flow Shop algorithm.
 */
enum class AlgorithmType {
    II,         // Iterative Improvement
    VND,        // Variable Neighbourhood Descent
    MEMETIC     // Memetic Algorithm
};


/**
 * @class FlowShopConfig
 * @brief The FlowShopConfig class parses and stores the command-line configuration parameters
 *       used to control the behavior of the Flow Shop algorithm.
 *       It is an abstract class that defines the interface for the configuration.
 * @field algorithmType The algorithm type to use.
 * @field instancePath The path to the instance file.
 */
class FlowShopConfig {
protected:
    AlgorithmType algorithmType;
    string instancePath;

public:

    /**
     * @brief Constructor for the FlowShopConfig class. It parses the first command-line arguments
     *        and sets the algorithm type and instance path.
     * @param argc The number of command-line arguments.
     * @param argv The command-line arguments.
     */
    FlowShopConfig(int argc, char* argv[]);

    /**
     * @brief default destructor
     */
    virtual ~FlowShopConfig() = default;

    /**
     * The getAlgorithmType function returns the algorithm type for the FlowShopConfig class.
     * @return The algorithm type.
     */
    [[nodiscard]] AlgorithmType getAlgorithmType() const;

    /**
     * The getInstancePath function returns the path to the instance file.
     * @return The path to the instance file.
     */
    [[nodiscard]] std::string getInstancePath() const;
};


#endif //FLOWSHOPSLS_FLOWSHOPCONFIG_HPP
