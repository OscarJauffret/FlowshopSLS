//
// Created by oscar on 28/03/2025.
//

#ifndef FLOWSHOPSLS_NEIGHBORHOODITERATOR_HPP
#define FLOWSHOPSLS_NEIGHBORHOODITERATOR_HPP


#include "../core/solution.hpp"

/**
 * @file neighborhoodIterator.hpp
 * @class NeighborhoodIterator
 * @brief Abstract class that defines the interface for a neighborhood iterator.
 * A neighborhood iterator is an object that iterates over the neighborhood of a solution.
 * The neighborhood of a solution is the set of solutions that can be obtained by applying a single move to the solution.
 * There are different types of neighborhood iterators, one for each type of move.
 * @see exchangeIterator.hpp, insertIterator.hpp, transposeIterator.hpp
 */
class NeighborhoodIterator {
    /**
     * @brief The reset function resets the iterator to the beginning of the neighborhood. This is used when the solution changes.
     */
    virtual void reset() = 0;

public:

    /**
     * @brief The destructor of the NeighborhoodIterator class.
     */
    virtual ~NeighborhoodIterator() = default;

    /**
     * @brief The hasNext function checks if there are more neighbors to explore in the neighborhood.
     * @return True if there are more neighbors to explore, false otherwise.
     */
    virtual bool hasNext() = 0;

    /**
     * @brief The next function returns the next neighbor in the neighborhood.
     * @return The next neighbor in the neighborhood.
     */
    virtual Solution next() = 0;

    /**
     * @brief The setSolution function sets the solution to explore the neighborhood of.
     * @param newSolution The new solution to explore the neighborhood of.
     */
    virtual void setSolution(const Solution& newSolution) = 0;
};

#endif //FLOWSHOPSLS_NEIGHBORHOODITERATOR_HPP
