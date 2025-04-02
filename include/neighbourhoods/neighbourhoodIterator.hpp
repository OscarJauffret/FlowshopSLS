//
// Created by oscar on 28/03/2025.
//

#ifndef FLOWSHOPSLS_neighbourHOODITERATOR_HPP
#define FLOWSHOPSLS_neighbourHOODITERATOR_HPP


#include "../core/solution.hpp"

/**
 * @file neighbourhoodIterator.hpp
 * @class NeighbourhoodIterator
 * @brief Abstract class that defines the interface for a neighbourhood iterator.
 * A neighbourhood iterator is an object that iterates over the neighbourhood of a solution.
 * The neighbourhood of a solution is the set of solutions that can be obtained by applying a single move to the solution.
 * There are different types of neighbourhood iterators, one for each type of move.
 * @see exchangeIterator.hpp, insertIterator.hpp, transposeIterator.hpp
 */
class NeighbourhoodIterator {
    /**
     * @brief The reset function resets the iterator to the beginning of the neighbourhood. This is used when the solution changes.
     */
    virtual void reset() = 0;

public:

    /**
     * @brief The destructor of the NeighbourhoodIterator class.
     */
    virtual ~NeighbourhoodIterator() = default;

    /**
     * @brief The hasNext function checks if there are more neighbours to explore in the neighbourhood.
     * @return True if there are more neighbours to explore, false otherwise.
     */
    virtual bool hasNext() = 0;

    /**
     * @brief The next function returns the next neighbour in the neighbourhood.
     * @return The next neighbour in the neighbourhood.
     */
    virtual Solution next() = 0;

    /**
     * @brief The setSolution function sets the solution to explore the neighbourhood of.
     * @param newSolution The new solution to explore the neighbourhood of.
     */
    virtual void setSolution(const Solution& newSolution) = 0;
};

#endif //FLOWSHOPSLS_neighbourHOODITERATOR_HPP
