cmake_minimum_required(VERSION 3.28)
project(FlowshopSLS)

set(CMAKE_CXX_STANDARD 17)

add_executable(FlowshopSLS src/main.cpp
        include/core/instance.hpp
        src/utils/dataAnalysis.cpp
        src/config.hpp
        include/utils/dataAnalysis.hpp
        src/core/instance.cpp
        src/core/solution.cpp
        include/core/solution.hpp
        include/initialization/initialization.hpp
        src/core/flowShopII.cpp
        include/core/flowShopII.hpp
        src/initialization/initialization.cpp
        include/neighborhoods/neighborhoodIterator.hpp
        include/neighborhoods/transposeIterator.hpp
        include/neighborhoods/exchangeIterator.hpp
        include/neighborhoods/insertIterator.hpp
)
