//
// Created by Oscar Jauffret on 01/05/2025.
//

#ifndef FLOWSHOPCONFIGII_HPP
#define FLOWSHOPCONFIGII_HPP

#include "flowShopConfig.hpp"
#include <string>

/**
* @class FlowShopConfigII
* @brief Class that contains the configuration parameters for iterative improvement for the Flow Shop algorithm.
* This class inherits from FlowShopConfig and adds specific parameters for the iterative improvement algorithm.
* @field pivotRule The pivoting rule to use for the algorithm.
* @field neighbourhood The neighbourhood structure to use for the algorithm.
* @field initMethod The initialization method to use for the algorithm.
*/
class FlowShopConfigII: public FlowShopConfig {
    PivotingRule pivotRule;
    NeighbourhoodStructure neighbourhood;
    InitializationMethod initMethod;

public:
    /**
     * The constructor for the FlowShopConfigII class. It parses the command-line arguments
     * @param argc The number of command-line arguments.
     * @param argv The command-line arguments.
     */
    FlowShopConfigII(int argc, char* argv[]);

    /**
     * The getPivotRule function returns the pivoting rule for the FlowShopConfigII class.
     * @return The pivoting rule.
     */
    [[nodiscard]] PivotingRule getPivotRule() const;

    /**
     * The getNeighbourhood function returns the neighbourhood structure for the FlowShopConfigII class.
     * @return The neighbourhood structure.
     */
    [[nodiscard]] NeighbourhoodStructure getNeighbourhood() const;

    /**
     * The getInitMethod function returns the initialization method for the FlowShopConfigII class.
     * @return The initialization method.
     */
    [[nodiscard]] InitializationMethod getInitMethod() const;
};



#endif //FLOWSHOPCONFIGII_HPP
