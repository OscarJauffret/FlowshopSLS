//
// Created by oscar on 28/03/2025.
//

#ifndef FLOWSHOPSLS_INSERTITERATOR_HPP
#define FLOWSHOPSLS_INSERTITERATOR_HPP

#include "neighbourhoodIterator.hpp"

#include <iostream>

/**
 * @file insertIterator.hpp
 * @class InsertIterator
 * @brief Class that implements the insert neighborhood iterator. It has methods to iterate over the insert neighborhood of a solution.
 * @field current - The current solution.
 * @field from - The index of the job to insert.
 * @field to - The index where to insert the job.
 * @field alpha - Used to limit the number of positions to insert the job.
 * @field hasValid - Indicates if the iterator has a valid position to insert the job.
 * @see neighbourhoodIterator.hpp
 */
class InsertIterator: public NeighbourhoodIterator {
    const Solution* current;
    uint8_t from, to;
    const uint8_t alpha;
    bool hasValid = false;

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
        hasValid = false;
        int n = current->getNumberOfJobs();
        while (from < n) {
            int maxTo = (alpha < 0 ? n - 1 : std::min(n - 1, from + alpha));
            if (to > maxTo) {
                // move to next from
                from++;
                to = (alpha < 0 ? 0 : std::max(0, from - alpha));
                continue;
            }
            if (to != from) {
                hasValid = true;
                break;
            }
            to++;
        }
    }

public:

    /**
     * @brief The constructor of the InsertIterator class. It initializes the iterator with the given solution.
     * @param sol The solution to iterate over.
     */
    explicit InsertIterator(const Solution &sol): current(&sol), from(0), to(0), alpha(-1) {
        moveToNextValid();
    }

    /**
     * @brief The constructor of the InsertIterator class. It initializes the iterator with the given solution.
     * @param sol The solution to iterate over.
     * @param alpha The parameter that controls the extent of the neighborhood search.
     */
    explicit InsertIterator(const Solution &sol, uint8_t alpha): current(&sol), from(0), to(0), alpha(alpha) {
        moveToNextValid();
    }

    /**
     * @brief The hasNext function checks if there are more neighbors to explore in the neighborhood.
     * In the insert neighborhood, we just stop if `from` is the last job.
     * @return True if there are more neighbors to explore, false otherwise.
     */
    bool hasNext() override {
        return hasValid;
    }

    /**
     * @brief The next function returns the next neighbor in the insert neighborhood.
     * It inserts the job `from` in the position `to` in the current solution.
     * @return The next neighbor in the insert neighborhood.
     */
    Solution next() override {
        Solution neighbor = current->insert(from, to++);
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

    /**
     * @brief The getFrom function returns the index of the job to insert.
     * @return The index of the job to insert.
     */
    [[nodiscard]] uint8_t getFrom() const {
        return from;
    }

    /**
     * @brief The getTo function returns the index where to insert the job.
     * @return The index where to insert the job.
     */
    [[nodiscard]] uint8_t getTo() const {
        return to;
    }

};

#endif //FLOWSHOPSLS_INSERTITERATOR_HPP
