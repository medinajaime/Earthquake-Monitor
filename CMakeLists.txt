cmake_minimum_required(VERSION 3.28)
project(Earthquake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Crow CONFIG REQUIRED)

# Include directories
include_directories("C:/curl-8.8.0/include" "C:/json-develop/include")

add_executable(Earthquake main.cpp
        EarthquakeMonitor.h
        EarthquakeFetcher.h
        FileNotification.h
        ConsoleNotification.h
        EarthquakeNotification.h)
target_link_libraries(Earthquake PRIVATE Crow::Crow asio::asio)


