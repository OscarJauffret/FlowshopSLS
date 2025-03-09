//
// Created by oscar on 07/03/2025.
//

#include <iostream>
#include "dataAnalysis.hpp"

using std::cout;
using std::endl;

int main() {
    cout << "Checking if all processing times are below 255..." << endl;
    if (checkAllProcessingTimes(config::instancePath)) {
        cout << "All processing times are below 255" << endl;
    } else {
        cout << "Some processing times exceed 255 -> Cannot use uint8_t" << endl;
    }

    return 0;
}