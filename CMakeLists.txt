cmake_minimum_required(VERSION 3.16)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
endif()
project(weatherpp)

set(CMAKE_CXX_STANDARD 17)
set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)
find_package(cpprestsdk REQUIRED)

add_executable(weatherpp src/main.cpp src/ConfigHandler.cpp src/ConfigHandler.h src/provider/OpenWeatherMap.cpp src/provider/OpenWeatherMap.h src/provider/IWeatherProvider.h src/provider/WeatherProviderFactory.cpp src/provider/WeatherProviderFactory.h src/provider/WeatherData.cpp src/provider/WeatherData.h src/GeoIPResolver.cpp src/GeoIPResolver.h src/Const.h)
target_link_libraries(weatherpp PRIVATE cpprestsdk::cpprest)
