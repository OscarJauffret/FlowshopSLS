//
// Created by oscar on 09/03/2025.
//

#ifndef FLOWSHOPSLS_INSTANCE_HPP
#define FLOWSHOPSLS_INSTANCE_HPP

#include <cstdint>
#include <vector>

using std::vector;

struct Instance {
    uint8_t jobs;
    uint8_t machines;

    vector<vector<uint8_t>> processingTimes;

};

#endif //FLOWSHOPSLS_INSTANCE_HPP
