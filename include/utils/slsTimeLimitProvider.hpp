//
// Created by Oscar Jauffret on 01/05/2025.
//

#ifndef MEMETICTIMELIMITPROVIDER_HPP
#define MEMETICTIMELIMITPROVIDER_HPP

#include <unordered_map>
#include <string>

/**
* @class SLSTimeLimitProvider
* @brief Class that provides time limits for the SLS algorithms based on the instance size and the VND time.
*/
class SLSTimeLimitProvider {
    static std::unordered_map<int, int> vndTimes;
    static bool isLoaded;

public:
    static void loadVNDTimes();
    static int getAllowedTime(int instanceSize);

};



#endif //MEMETICTIMELIMITPROVIDER_HPP
