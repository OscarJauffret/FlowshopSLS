//
// Created by oscar on 28/03/2025.
//

#ifndef FLOWSHOPSLS_TRANSPOSEITERATOR_HPP
#define FLOWSHOPSLS_TRANSPOSEITERATOR_HPP


#include "neighborhoodIterator.hpp"

class TransposeIterator: public NeighborhoodIterator{
    const Solution* current;
    uint8_t position;

public:
    explicit TransposeIterator(const Solution& sol): current(&sol), position(0) {}

    bool hasNext() override {
        return position < current->getNumberOfJobs() - 1;
    }

    Solution next() override {
        return current->transpose(position++);
    }

    void reset() override {
        position = 0;
    }

    void setSolution(const Solution& newSolution) override {
        current = &newSolution;
        reset();
    }

};


#endif //FLOWSHOPSLS_TRANSPOSEITERATOR_HPP
