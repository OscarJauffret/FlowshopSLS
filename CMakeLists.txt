cmake_minimum_required(VERSION 3.28)
project(FlowshopSLS)

set(CMAKE_CXX_STANDARD 17)

add_executable(FlowshopSLS src/main.cpp
        src/instance.hpp
        src/dataAnalysis.cpp
        src/config.hpp
        src/dataAnalysis.hpp)
