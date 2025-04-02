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
 * @class FlowShopConfig
 * @brief The FlowShopConfig class parses and stores the command-line configuration parameters
 *       used to control the behavior of the Flow Shop algorithm.
 *       The configuration parameters are the pivoting rule, the neighbourhood structure, and the initialization method.
 * @field pivotRule The pivoting rule to use.
 * @field neighbourhood The neighbourhood structure to use.
 * @field initMethod The initialization method to use.
 */
class FlowShopConfig {
    string instancePath;
    PivotingRule pivotRule;
    NeighbourhoodStructure neighbourhood;
    InitializationMethod initMethod;

public:

    /**
     * @brief The constructor of the FlowShopConfig class. It parses the command-line arguments and initializes the configuration parameters.
     * @param argc The number of command-line arguments.
     * @param argv The command-line arguments.
     */
    explicit FlowShopConfig(int argc, char* argv[]);

    /**
     * @brief The getInstancePath function returns the path to the instance file.
     * @return The path to the instance file.
     */
    [[nodiscard]] string getInstancePath() const;

    /**
     * @brief The getPivotRule function returns the pivoting rule to use.
     * @return The pivoting rule to use.
     */
    [[nodiscard]] PivotingRule getPivotRule() const;

    /**
     * @brief The getNeighbourhood function returns the neighbourhood structure to use.
     * @return The neighbourhood structure to use.
     */
    [[nodiscard]] NeighbourhoodStructure getNeighbourhood() const;

    /**
     * @brief The getInitMethod function returns the initialization method to use.
     * @return The initialization method to use.
     */
    [[nodiscard]] InitializationMethod getInitMethod() const;
};


#endif //FLOWSHOPSLS_FLOWSHOPCONFIG_HPP
