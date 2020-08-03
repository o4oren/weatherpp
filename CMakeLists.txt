cmake_minimum_required(VERSION 3.17)
project(weatherpp)

set(CMAKE_CXX_STANDARD 17)
find_package(cpprestsdk REQUIRED)

add_executable(weatherpp src/main.cpp src/ConfigHandler.cpp src/ConfigHandler.h src/provider/OpenWeatherMap.cpp src/provider/OpenWeatherMap.h)
target_link_libraries(weatherpp PRIVATE cpprestsdk::cpprest)
