//
// Created by oscar on 09/03/2025.
//

#ifndef FLOWSHOPSLS_DATAANALYSIS_HPP
#define FLOWSHOPSLS_DATAANALYSIS_HPP

#include <string>
#include "../config.hpp"

using std::string;

/**
 * @brief Check if the processing times of a file are below 255. This function was used to check if we could use uint8_t to store the processing times
 * @param filename Path to the file
 * @return True if all the processing times are below 255, false otherwise
 */
bool checkProcessingTimes(const string& filename);

/**
 * @brief Check if the processing times of all the files in a directory are below 255
 * @param directory Path to the directory
 * @return True if all the processing times are below 255, false otherwise
 */
bool checkAllProcessingTimes(const string& directory);

#endif //FLOWSHOPSLS_DATAANALYSIS_HPP
