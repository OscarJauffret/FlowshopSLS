//
// Created by oscar on 28/03/2025.
//

#ifndef FLOWSHOPSLS_TRANSPOSEITERATOR_HPP
#define FLOWSHOPSLS_TRANSPOSEITERATOR_HPP

#include "neighborhoodIterator.hpp"

/**
 * @file transposeIterator.hpp
 * @class TransposeIterator
 * @brief Class that implements the transpose neighborhood iterator. It has methods to iterate over the transpose neighborhood of a solution.
 * @field current - The current solution.
 * @field position - The index of the job to transpose.
 * @see neighborhoodIterator.hpp
 */
class TransposeIterator: public NeighborhoodIterator{
    const Solution* current;
    uint8_t position;

    /**
     * @brief The reset function resets the iterator to the beginning of the neighborhood. This is used when the solution changes.
     */
    void reset() override {
        position = 0;
    }

public:

    /**
     * @brief The constructor of the TransposeIterator class. It initializes the iterator with the given solution.
     * @param sol The solution to iterate over.
     */
    explicit TransposeIterator(const Solution& sol): current(&sol), position(0) {}

    /**
     * @brief The hasNext function checks if there are more neighbors to explore in the neighborhood.
     * In the transpose neighborhood, we just stop if the position is the second to last job because we need to transpose two consecutive jobs.
     * @return True if there are more neighbors to explore, false otherwise.
     */
    bool hasNext() override {
        return position < current->getNumberOfJobs() - 1;
    }

    /**
     * @brief The next function returns the next neighbor in the transpose neighborhood.
     * @return The next neighbor in the transpose neighborhood.
     */
    Solution next() override {
        return current->transpose(position++);
    }

    /**
     * @brief The setSolution function sets the solution to explore the neighborhood of.
     * @param newSolution The new solution to explore the neighborhood of.
     */
    void setSolution(const Solution& newSolution) override {
        current = &newSolution;
        reset();
    }

};


#endif //FLOWSHOPSLS_TRANSPOSEITERATOR_HPP
