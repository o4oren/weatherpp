#ifndef WEATHERPP_SRC_PROVIDER_WEATHERDATA_H
#define WEATHERPP_SRC_PROVIDER_WEATHERDATA_H
#include <ctime>
#include <string>
#include <cpprest/details/basic_types.h>

using utility:: string_t;

/**
 * Class to represent the weather data returned from the provider.
 * Using cpprest's string_t to support cross platform, and prevent dealing with this when implementing a new provider.
 * Representation methods convert to an std::string to avoid dealing with this elsewhere.
 */
class WeatherData
{
  public:
    string_t units;
    int clouds;
    double latitude;
    double longitude;
    time_t timestamp;
    string_t city;
    string_t country;
    int humidity;
    int pressure;
    int temp;
    int max;
    int min;
    int feelsLike;
    int visibility;
    time_t sunrise;
    time_t sunset;
    string_t description;
    int windDegrees;
    double windSpeed;
    string_t icon;
    std::string getShortRepresentation();
    static string_t getDegreesSymbol(const string_t &units);
};

#endif // WEATHERPP_SRC_PROVIDER_WEATHERDATA_H
