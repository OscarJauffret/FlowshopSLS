cmake_minimum_required(VERSION 3.26)
project(pfsp)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

add_executable(pfsp-ii
        src/main.cpp
        src/core/instance.cpp
        src/core/solution.cpp
        src/core/flowShopII.cpp
        src/initialization/initialization.cpp
        src/utils/dataAnalysis.cpp
        src/config/flowShopConfig.cpp
        src/core/flowShopVnd.cpp
        src/utils/runLogger.cpp
        src/core/flowShopMemetic.cpp
        src/utils/memeticTimeLimitProvider.cpp
        src/config/flowShopConfigII.cpp
        src/config/flowShopConfigVnd.cpp
        include/config/flowShopConfigVnd.hpp
        src/config/flowShopConfigMemetic.cpp
        include/config/flowShopConfigMemetic.hpp
)
