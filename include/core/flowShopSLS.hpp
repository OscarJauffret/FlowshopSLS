//
// Created by oscar on 01/04/2025.
//

#ifndef PFSP_II_FLOWSHOPSLS_HPP
#define PFSP_II_FLOWSHOPSLS_HPP

#include "solution.hpp"
#include "../initialization/initialization.hpp"
#include "../neighborhoods/neighborhoodIterator.hpp"
#include "../neighborhoods/transposeIterator.hpp"
#include "../neighborhoods/exchangeIterator.hpp"
#include "../neighborhoods/insertIterator.hpp"
#include "../utils/flowShopConfig.hpp"

class FlowShopSLS {
protected:

    Solution candidate;                                         // The current candidate solution
    PivotingRule pivotingRule;                                  // The pivoting rule to use
    std::unique_ptr<NeighborhoodIterator> neighborhoodIterator; // The neighborhood iterator to use

    /**
     * @brief The step function performs a single step of the SLS algorithm. It uses the neighborhood iterator to explore the solution space.
     * @return The best neighbor found in the neighborhood or the first neighbor that improves the current solution depending on the pivoting rule.
     */
    virtual Solution step() = 0;

    /**
     * @brief The constructor of the FlowShoSLS class. It initializes the algorithm with the given instance, pivoting rule, initialization method, and random number generator.
     * @param instance The instance of the problem.
     * @param pivotRule The pivoting rule to use.
     * @param initMethod The initialization method to use.
     * @param rng The random number generator.
     */
    FlowShopSLS(const Instance &instance, PivotingRule pivotRule, InitializationMethod initMethod, std::mt19937 rng):
            pivotingRule(pivotRule),
            candidate(initMethod == InitializationMethod::RANDOM
                    ? initialization::random(instance, rng)
                    : initialization::simplifiedRZ(instance)) {}
public:

    /**
     * @brief Destructor of the FlowShopSLS class, virtual to allow inheritance.
     */
    virtual ~FlowShopSLS() = default;

    /**
     * @brief The run function runs the SLS algorithm until no improvement is found.
     * @return The best solution found by the algorithm.
     */
    virtual Solution run() = 0;
};

#endif //PFSP_II_FLOWSHOPSLS_HPP
