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
 *       The configuration parameters are the pivoting rule, the neighbourhood structure, and the initialization method.
 * @field algorithmType The algorithm type to use (Iterative Improvement or Variable Neighbourhood Descent).
 * @field instancePath The path to the instance file.
 * @field pivotRule The pivoting rule to use. (only for Iterative Improvement)
 * @field neighbourhood The neighbourhood structure to use. (only for Iterative Improvement)
 * @field initMethod The initialization method to use. (only for Iterative Improvement)
 * @field vndStrategy The VND strategy to use (only for Variable Neighbourhood Descent)
 * @field populationSize The size of the population to use (only for Memetic algorithm)
 */
class FlowShopConfig {
    AlgorithmType algorithmType;
    string instancePath;

    // Iterative improvement
    PivotingRule pivotRule;
    NeighbourhoodStructure neighbourhood;
    InitializationMethod initMethod;

    // Variable neighbourhood descent
    VNDStrategy vndStrategy;

    // Memetic algorithm
    int populationSize;

    /**
     * @brief The parseArgumentsII function parses the command-line arguments for the Iterative Improvement algorithm.
     * @param argc The number of command-line arguments.
     * @param argv The command-line arguments.
     */
    void parseArgumentsII(int argc, char* argv[]);

    /**
     * @brief The parseArgumentsVND function parses the command-line arguments for the Variable Neighbourhood Descent algorithm.
     * @param argc The number of command-line arguments.
     * @param argv The command-line arguments.
     */
    void parseArgumentsVND(int argc, char* argv[]);

    /**
     * @brief The parseArgumentsMemetic function parses the command-line arguments for the memetic algorithm.
     * @param argc The number of command-line arguments.
     * @param argv The command-line arguments.
     */
    void parseArgumentsMemetic(int argc, char* argv[]);

public:

    /**
     * @brief The constructor of the FlowShopConfig class. It parses the command-line arguments and initializes the configuration parameters.
     * @param argc The number of command-line arguments.
     * @param argv The command-line arguments.
     */
    explicit FlowShopConfig(int argc, char* argv[]);

    /**
     * @brief The getAlgorithmType function returns the algorithm type to use.
     * @return The algorithm type to use.
     */
    [[nodiscard]] AlgorithmType getAlgorithmType() const;

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

    /**
     * @brief The getVNDStrategy function returns the VND strategy to use.
     * @return The VND strategy to use.
     */
    [[nodiscard]] VNDStrategy getVNDStrategy() const;

    /**
     * @brief The getPopulationSize function returns the population size to use.
     * @return The population size to use.
     */
    [[nodiscard]] int getPopulationSize() const;
};


#endif //FLOWSHOPSLS_FLOWSHOPCONFIG_HPP
