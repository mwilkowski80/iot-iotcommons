cmake_minimum_required(VERSION 3.14)
project(iotcommons)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/core)
add_library(iotcommons src/core/WifiBlinkLed.cpp src/core/WifiNetworkTask.cpp src/core/BlinkingLed.cpp)
