//
// Created by oscar on 28/03/2025.
//

#ifndef FLOWSHOPSLS_INSERTITERATOR_HPP
#define FLOWSHOPSLS_INSERTITERATOR_HPP

#include "neighborhoodIterator.hpp"

class InsertIterator: public NeighborhoodIterator {
    const Solution &current;
    uint8_t from, to;

public:

    explicit InsertIterator(const Solution &sol): current(sol), from(0), to(1) {
        moveToNextValid();
    }

    bool hasNext() override {
        return from < current.getNumberOfJobs();
    }

    Solution next() override {
        Solution neighbor = current.insert(from, to++);
        if (to == current.getNumberOfJobs()) {
            from++;
            to = from + 1;
        }
        moveToNextValid();
        return neighbor;
    }

    void reset() override {
        from = 0;
        to = 1;
        moveToNextValid();
    }

private:
    void moveToNextValid() {
        while (from < current.getNumberOfJobs() && from == to) {
            to++;
            if (to == current.getNumberOfJobs()) {
                from++;
                to = 0;
            }
        }
    }

};

#endif //FLOWSHOPSLS_INSERTITERATOR_HPP
