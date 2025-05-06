//
// Created by Oscar Jauffret on 01/05/2025.
//

#ifndef FLOWSHOPCONFIGMEMETIC_HPP
#define FLOWSHOPCONFIGMEMETIC_HPP

#include "flowShopConfig.hpp"

enum class LocalSearchMethod {
    NONE,
    II,
    VND
};

/**
 * @brief The FlowShopConfigMemetic class is a configuration class for the memetic algorithm.
 * It inherits from the FlowShopConfig class and adds additional parameters specific to the memetic algorithm.
 * @field populationSize - The size of the population for the memetic algorithm.
 * @field mutationRate - The mutation rate for the memetic algorithm.
 * @field localSearchMethod - The local search method to be used in the memetic algorithm.
 */
class FlowShopConfigMemetic: public FlowShopConfig {
    int populationSize;
    float mutationRate;
    LocalSearchMethod localSearchMethod;

public:

    /**
     * The constructor for the FlowShopConfigMemetic class. It parses the command-line arguments
     * @param argc The number of command-line arguments.
     * @param argv The command-line arguments.
     */
    FlowShopConfigMemetic(int argc, char* argv[]);

    /**
     * @brief The getPopulationSize function returns the population size for the FlowShopConfigMemetic class.
     * @return The population size.
     */
    [[nodiscard]] int getPopulationSize() const;

    /**
     * @brief The getMutationRate function returns the mutation rate for the FlowShopConfigMemetic class.
     * @return The mutation rate.
     */
    [[nodiscard]] float getMutationRate() const;

    /**
     * @brief The getLocalSearchMethod function returns the local search method for the FlowShopConfigMemetic class.
     * @return The local search method.
     */
    [[nodiscard]] LocalSearchMethod getLocalSearchMethod() const;


};



#endif //FLOWSHOPCONFIGMEMETIC_HPP
