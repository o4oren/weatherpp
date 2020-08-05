cmake_minimum_required(VERSION 3.17)
project(weatherpp)

set(CMAKE_CXX_STANDARD 17)
find_package(cpprestsdk REQUIRED)

add_executable(weatherpp src/main.cpp src/ConfigHandler.cpp src/ConfigHandler.h src/provider/OpenWeatherMap.cpp src/provider/OpenWeatherMap.h src/provider/IWeatherProvider.h src/provider/WeatherProviderFactory.cpp src/provider/WeatherProviderFactory.h src/provider/WeatherData.cpp src/provider/WeatherData.h src/GeoIPResolver.cpp src/GeoIPResolver.h)
target_link_libraries(weatherpp PRIVATE cpprestsdk::cpprest)
