//
// Created by oscar on 28/03/2025.
//

#ifndef FLOWSHOPSLS_EXCHANGEITERATOR_HPP
#define FLOWSHOPSLS_EXCHANGEITERATOR_HPP

#include "neighborhoodIterator.hpp"

class ExchangeIterator: public NeighborhoodIterator {
    const Solution* current;
    uint8_t i, j;

public:

    explicit ExchangeIterator(const Solution &sol): current(&sol), i(0), j(1) {}

    bool hasNext() override {
        return i < current->getNumberOfJobs() - 1;
    }

    Solution next() override {
        Solution neighbor = current->exchange(i, j++);
        if (j == current->getNumberOfJobs()) {
            i++;
            j = i + 1;
        }
        return neighbor;
    }

    void reset() override {
        i = 0;
        j = 1;
    }

    void setSolution(const Solution& newSolution) override {
        current = &newSolution;
        reset();
    }
};

#endif //FLOWSHOPSLS_EXCHANGEITERATOR_HPP
