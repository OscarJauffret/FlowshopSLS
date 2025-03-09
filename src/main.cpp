//
// Created by oscar on 07/03/2025.
//

#include <iostream>
#include "instance.hpp"
#include "config.hpp"

using std::cout;
using std::endl;

int main() {
    string instancePath = config::instancePath + "ta051";
    Instance instance(instancePath);
    cout << instance << endl;
    return 0;
}