//
// Created by oscar on 28/03/2025.
//

#ifndef FLOWSHOPSLS_NEIGHBORHOODITERATOR_HPP
#define FLOWSHOPSLS_NEIGHBORHOODITERATOR_HPP


#include "../core/solution.hpp"

class NeighborhoodIterator {
public:
    virtual ~NeighborhoodIterator() = default;

    virtual bool hasNext() = 0;
    virtual Solution next() = 0;
    virtual void reset() = 0;
};

#endif //FLOWSHOPSLS_NEIGHBORHOODITERATOR_HPP
