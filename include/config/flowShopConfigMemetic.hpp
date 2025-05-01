//
// Created by Oscar Jauffret on 01/05/2025.
//

#ifndef FLOWSHOPCONFIGMEMETIC_HPP
#define FLOWSHOPCONFIGMEMETIC_HPP

#include "flowShopConfig.hpp"


class FlowShopConfigMemetic: public FlowShopConfig {
    int populationSize;

public:

    /**
     * The constructor for the FlowShopConfigMemetic class. It parses the command-line arguments
     * @param argc The number of command-line arguments.
     * @param argv The command-line arguments.
     */
    FlowShopConfigMemetic(int argc, char* argv[]);

    /**
     * The getPopulationSize function returns the population size for the FlowShopConfigMemetic class.
     * @return The population size.
     */
    [[nodiscard]] int getPopulationSize() const;
};



#endif //FLOWSHOPCONFIGMEMETIC_HPP
