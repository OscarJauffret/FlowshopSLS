cmake_minimum_required(VERSION 3.28)
project(FlowshopSLS)

set(CMAKE_CXX_STANDARD 17)

add_executable(FlowshopSLS src/main.cpp
        src/include/instance.hpp
        src/dataAnalysis.cpp
        src/config.hpp
        src/include/dataAnalysis.hpp
        src/instance.cpp
        src/solution.cpp
        src/include/solution.hpp
        src/include/initialization.hpp)
