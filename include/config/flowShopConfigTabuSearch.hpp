//
// Created by oscar on 06/05/2025.
//

#ifndef PFSP_FLOWSHOPCONFIGTABUSEARCH_HPP
#define PFSP_FLOWSHOPCONFIGTABUSEARCH_HPP

#include "flowShopConfig.hpp"

class FlowShopConfigTabuSearch: public FlowShopConfig {

    int tabuTenure;
    int alpha;
    int maxGenerations;
    int maxStuck;

public:

    /**
     * The constructor for the FlowShopConfigTabuSearch class. It parses the command-line arguments
     * @param argc The number of command-line arguments.
     * @param argv The command-line arguments.
     */
    FlowShopConfigTabuSearch(int argc, char* argv[]);

    /**
     * @brief The getTabuTenure function returns the tabu tenure for the FlowShopConfigTabuSearch class.
     * @return The tabu tenure.
     */
    [[nodiscard]] int getTabuTenure() const;

    /**
     * @brief The getAlpha function returns the alpha parameter for the FlowShopConfigTabuSearch class.
     * @return The alpha parameter.
     */
    [[nodiscard]] int getAlpha() const;

    /**
     * @brief The getMaxGenerations function returns the maximum number of generations for the FlowShopConfigTabuSearch class.
     * @return The maximum number of generations.
     */
    [[nodiscard]] int getMaxGenerations() const;

    /**
     * @brief The getMaxStuck function returns the maximum number of generations without improvement for the FlowShopConfigTabuSearch class.
     * @return The maximum number of generations without improvement.
     */
    [[nodiscard]] int getMaxStuck() const;

};


#endif //PFSP_FLOWSHOPCONFIGTABUSEARCH_HPP
