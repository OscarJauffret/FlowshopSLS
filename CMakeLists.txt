cmake_minimum_required(VERSION 3.26)
project(pfsp-ii)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

add_executable(pfsp-ii
        src/main.cpp
        src/core/instance.cpp
        src/core/solution.cpp
        src/core/flowShopII.cpp
        src/initialization/initialization.cpp
        src/utils/dataAnalysis.cpp
        src/utils/flowShopConfig.cpp
)
