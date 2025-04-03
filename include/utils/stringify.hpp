//
// Created by oscar on 02/04/2025.
//

#ifndef PFSP_II_STRINGIFY_HPP
#define PFSP_II_STRINGIFY_HPP

#include <string>
#include "flowShopConfig.hpp"

using std::string;

namespace stringify {
    inline string pivot(PivotingRule p) {
        switch (p) {
            case PivotingRule::FIRST_IMPROVEMENT: return "first";
            case PivotingRule::BEST_IMPROVEMENT: return "best";
        }

        return "unknown";
    }

    inline string neighbourhood(NeighbourhoodStructure n) {
        switch (n) {
            case NeighbourhoodStructure::TRANSPOSE: return "transpose";
            case NeighbourhoodStructure::EXCHANGE: return "exchange";
            case NeighbourhoodStructure::INSERT: return "insert";
        }

        return "unknown";
    }

    inline string init(InitializationMethod i) {
        switch (i) {
            case InitializationMethod::RANDOM: return "random";
            case InitializationMethod::SIMPLIFIED_RZ: return "srz";
        }

        return "unknown";
    }

    inline string vnd(VNDStrategy v) {
        switch (v) {
            case VNDStrategy::TEI: return "tei";
            case VNDStrategy::TIE: return "tie";
        }

        return "unknown";
    }
}

#endif //PFSP_II_STRINGIFY_HPP
