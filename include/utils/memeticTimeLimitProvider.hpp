//
// Created by Oscar Jauffret on 01/05/2025.
//

#ifndef MEMETICTIMELIMITPROVIDER_HPP
#define MEMETICTIMELIMITPROVIDER_HPP

#include <unordered_map>
#include <string>

/**
* @class MemeticTimeLimitProvider
* @brief Class that provides time limits for the memetic algorithm based on the instance size and the VND time.
*/
class MemeticTimeLimitProvider {
    static std::unordered_map<int, int> vndTimes;
    static bool isLoaded;

public:
    static void loadVNDTimes();
    static int getMemeticAllowedTime(int instanceSize);

};



#endif //MEMETICTIMELIMITPROVIDER_HPP
