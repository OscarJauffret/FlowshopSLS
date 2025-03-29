//
// Created by oscar on 29/03/2025.
//

#ifndef FLOWSHOPSLS_FLOWSHOPCONFIG_HPP
#define FLOWSHOPSLS_FLOWSHOPCONFIG_HPP

#include "../neighborhoods/neighborhoodIterator.hpp"
#include "../initialization/initialization.hpp"


enum class InitializationMethod {
    RANDOM,
    SIMPLIFIED_RZ
};

enum class NeighbourhoodStructure {
    TRANSPOSE,
    EXCHANGE,
    INSERT
};

enum class PivotingRule {
    FIRST_IMPROVEMENT,
    BEST_IMPROVEMENT
};

class FlowShopConfig {
    PivotingRule pivotRule;
    NeighbourhoodStructure neighbourhood;
    InitializationMethod initMethod;

public:

    explicit FlowShopConfig(int argc, char* argv[]);
    [[nodiscard]] PivotingRule getPivotRule() const;
    [[nodiscard]] NeighbourhoodStructure getNeighbourhood() const;
    [[nodiscard]] InitializationMethod getInitMethod() const;
};


#endif //FLOWSHOPSLS_FLOWSHOPCONFIG_HPP
