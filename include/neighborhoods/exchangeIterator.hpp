//
// Created by oscar on 28/03/2025.
//

#ifndef FLOWSHOPSLS_EXCHANGEITERATOR_HPP
#define FLOWSHOPSLS_EXCHANGEITERATOR_HPP

#include "neighborhoodIterator.hpp"

/**
 * @file exchangeIterator.hpp
 * @class ExchangeIterator
 * @brief Class that implements the exchange neighborhood iterator. It has methods to iterate over the exchange neighborhood of a solution.
 * @field current - The current solution.
 * @field i - The index of the first job to exchange.
 * @field j - The index of the second job to exchange.
 * @see neighborhoodIterator.hpp
 */
class ExchangeIterator: public NeighborhoodIterator {
    const Solution* current;
    uint8_t i, j;

    /**
     * @brief The reset function resets the iterator to the beginning of the neighborhood. This is used when the solution changes.
     */
    void reset() override {
        i = 0;
        j = 1;
    }

public:

    /**
     * @brief The constructor of the ExchangeIterator class. It initializes the iterator with the given solution.
     * @param sol The solution to iterate over.
     */
    explicit ExchangeIterator(const Solution &sol): current(&sol), i(0), j(1) {}

    /**
     * @brief The hasNext function checks if there are more neighbors to explore in the neighborhood.
     * In the exchange neighborhood, we just stop if i the second to last job. Since exchange is symmetric, we only need to iterate over couples (i, j) where i < j.
     * @return True if there are more neighbors to explore, false otherwise.
     */
    bool hasNext() override {
        return i < current->getNumberOfJobs() - 1;
    }

    /**
     * @brief The next function returns the next neighbor in the exchange neighborhood.
     * It exchanges the jobs i and j in the current solution.
     * Since exchange is symmetric, we only need to iterate over couples (i, j) where i < j.
     * @return The next neighbor in the exchange neighborhood.
     */
    Solution next() override {
        Solution neighbor = current->exchange(i, j++);
        if (j == current->getNumberOfJobs()) {
            i++;
            j = i + 1;
        }
        return neighbor;
    }

    /**
     * @brief The setSolution function sets the current solution to iterate over.
     * It resets the iterator to the beginning of the neighborhood.
     * @param newSolution The new solution to iterate over.
     */
    void setSolution(const Solution& newSolution) override {
        current = &newSolution;
        reset();
    }
};

#endif //FLOWSHOPSLS_EXCHANGEITERATOR_HPP
