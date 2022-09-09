cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(UDP VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(bifrost)
add_subdirectory(dream)
