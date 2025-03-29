//
// Created by oscar on 28/03/2025.
//

#ifndef FLOWSHOPSLS_INSERTITERATOR_HPP
#define FLOWSHOPSLS_INSERTITERATOR_HPP

#include "neighborhoodIterator.hpp"

#include <iostream>

/**
 * @file insertIterator.hpp
 * @class InsertIterator
 * @brief Class that implements the insert neighborhood iterator. It has methods to iterate over the insert neighborhood of a solution.
 * @field current - The current solution.
 * @field from - The index of the job to insert.
 * @field to - The index where to insert the job.
 * @see neighborhoodIterator.hpp
 */
class InsertIterator: public NeighborhoodIterator {
    const Solution* current;
    uint8_t from, to;

    /**
     * @brief The reset function resets the iterator to the beginning of the neighborhood. This is used when the solution changes.
     */
    void reset() override {
        from = 0;
        to = 1;
        moveToNextValid();
    }

    /**
     * @brief The moveToNextValid function moves the iterator to the next valid position in the neighborhood.
     * Basically, it moves the iterator to the next position where from != to.
     */
    void moveToNextValid() {
        while (from < current->getNumberOfJobs() && from == to) {
            to++;
            if (to >= current->getNumberOfJobs()) {
                from++;
                to = 0;
            }
        }
    }

public:

    /**
     * @brief The constructor of the InsertIterator class. It initializes the iterator with the given solution.
     * @param sol The solution to iterate over.
     */
    explicit InsertIterator(const Solution &sol): current(&sol), from(0), to(0) {
        moveToNextValid();
    }

    /**
     * @brief The hasNext function checks if there are more neighbors to explore in the neighborhood.
     * In the insert neighborhood, we just stop if `from` is the last job.
     * @return True if there are more neighbors to explore, false otherwise.
     */
    bool hasNext() override {
        return from < current->getNumberOfJobs();
    }

    /**
     * @brief The next function returns the next neighbor in the insert neighborhood.
     * It inserts the job `from` in the position `to` in the current solution.
     * @return The next neighbor in the insert neighborhood.
     */
    Solution next() override {
        Solution neighbor = current->insert(from, to++);
        if (to >= current->getNumberOfJobs()) {
            from++;
            to = 0;
        }
        moveToNextValid();
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

#endif //FLOWSHOPSLS_INSERTITERATOR_HPP
