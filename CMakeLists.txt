cmake_minimum_required(VERSION 3.28)
project(Earthquake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Crow CONFIG REQUIRED)
find_package(CURL REQUIRED)

# Add the executable
add_executable(Earthquake main.cpp
        EarthquakeMonitor.h
        EarthquakeFetcher.h
        FileNotification.h
        ConsoleNotification.h
        EarthquakeNotification.h
        CombinedNotification.h)

# Link libraries
target_link_libraries(Earthquake PRIVATE Crow::Crow asio::asio)
target_link_libraries(Earthquake PRIVATE CURL::libcurl)

# Include directories
target_include_directories(Earthquake PRIVATE
        "C:/curl-8.8.0/include"
        "C:/json-develop/include"
)

# Library directories
link_directories("C:/curl-8.8.0/lib")

# Define _CRT_SECURE_NO_WARNINGS
target_compile_definitions(Earthquake PRIVATE _CRT_SECURE_NO_WARNINGS)