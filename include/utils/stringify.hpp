//
// Created by oscar on 02/04/2025.
//

#ifndef PFSP_II_STRINGIFY_HPP
#define PFSP_II_STRINGIFY_HPP

#include <string>
#include "../config/flowShopConfig.hpp"

using std::string;

/**
 * @namespace stringify
 * @brief The stringify namespace contains functions to convert enumeration types to strings.
 */
namespace stringify {
    /**
     * @brief Convert the PivotingRule enumeration to a string.
     * @param p The PivotingRule enumeration value.
     * @return The string representation of the PivotingRule enumeration value.
     */
    inline string pivot(PivotingRule p) {
        switch (p) {
            case PivotingRule::FIRST_IMPROVEMENT: return "first";
            case PivotingRule::BEST_IMPROVEMENT: return "best";
        }

        return "unknown";
    }

    /**
     * @brief Convert the NeighbourhoodStructure enumeration to a string.
     * @param n The NeighbourhoodStructure enumeration value.
     * @return The string representation of the NeighbourhoodStructure enumeration value.
     */
    inline string neighbourhood(NeighbourhoodStructure n) {
        switch (n) {
            case NeighbourhoodStructure::TRANSPOSE: return "transpose";
            case NeighbourhoodStructure::EXCHANGE: return "exchange";
            case NeighbourhoodStructure::INSERT: return "insert";
        }

        return "unknown";
    }

    /**
     * @brief Convert the InitializationMethod enumeration to a string.
     * @param i The InitializationMethod enumeration value.
     * @return The string representation of the InitializationMethod enumeration value.
     */
    inline string init(InitializationMethod i) {
        switch (i) {
            case InitializationMethod::RANDOM: return "random";
            case InitializationMethod::SIMPLIFIED_RZ: return "srz";
        }

        return "unknown";
    }

    /**
     * @brief Convert the AlgorithmType enumeration to a string.
     * @param v The AlgorithmType enumeration value.
     * @return The string representation of the AlgorithmType enumeration value.
     */
    inline string vnd(VNDStrategy v) {
        switch (v) {
            case VNDStrategy::TEI: return "tei";
            case VNDStrategy::TIE: return "tie";
        }

        return "unknown";
    }
}

#endif //PFSP_II_STRINGIFY_HPP
