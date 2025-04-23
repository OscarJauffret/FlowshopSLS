//
// Created by oscar on 01/04/2025.
//

#ifndef PFSP_II_FLOWSHOPSLS_HPP
#define PFSP_II_FLOWSHOPSLS_HPP

#include "solution.hpp"
#include "../initialization/initialization.hpp"
#include "../utils/flowShopConfig.hpp"
#include "../neighbourhoods/exchangeIterator.hpp"
#include "../neighbourhoods/insertIterator.hpp"
#include "../neighbourhoods/neighbourhoodIterator.hpp"
#include "../neighbourhoods/transposeIterator.hpp"
#include "flowShopSolver.hpp"



/**
 * @file flowShopSLS.hpp
 * @class FlowShopSLS
 * @brief The FlowShopSLS class is an abstract class that represents a Stochastic Local Search algorithm for the Flow Shop Scheduling Problem.
 * It uses a neighborhood iterator and a pivoting rule to explore the solution space.
 * @field candidate The current candidate solution.
 * @field pivotingRule The pivoting rule to use.
 * @see flowShopII.hpp, flowShopVnd.hpp in the include/core directory
 */
class FlowShopSLS: public FlowShopSolver {
protected:

    Solution candidate;                                         // The current candidate solution
    PivotingRule pivotingRule;                                  // The pivoting rule to use

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
                    : initialization::simplifiedRZ(instance, rng)) {}
public:

    /**
     * @brief The run function runs the SLS algorithm until no improvement is found.
     * @return The best solution found by the algorithm.
     */
    Solution run() override {
        Solution prev(candidate);
        do {
            prev = candidate;
            candidate = step();
        } while (candidate.getFitness() < prev.getFitness());

        return candidate;
    }
};

#endif //PFSP_II_FLOWSHOPSLS_HPP
