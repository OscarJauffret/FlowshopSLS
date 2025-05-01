//
// Created by Oscar Jauffret on 01/05/2025.
//

#ifndef FLOWSHOPCONFIGVND_HPP
#define FLOWSHOPCONFIGVND_HPP

#include "flowShopConfig.hpp"

class FlowShopConfigVND: public FlowShopConfig {
    VNDStrategy vndStrategy;

public:
    /**
     * The constructor for the FlowShopConfigVND class. It parses the command-line arguments
     * @param argc The number of command-line arguments.
     * @param argv The command-line arguments.
     */
    FlowShopConfigVND(int argc, char* argv[]);

    /**
     * The getVNDStrategy function returns the VND strategy for the FlowShopConfigVND class.
     * @return The VND strategy.
     */
    [[nodiscard]] VNDStrategy getVNDStrategy() const;
};



#endif //FLOWSHOPCONFIGVND_HPP
