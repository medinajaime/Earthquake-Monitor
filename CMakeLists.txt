cmake_minimum_required(VERSION 3.28)
project(Earthquake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories("C:/curl-8.8.0/include" "C:/json-develop/include")


add_executable(Earthquake main.cpp)
