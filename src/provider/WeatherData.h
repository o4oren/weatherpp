#ifndef WEATHERPP_SRC_PROVIDER_WEATHERDATA_H
#define WEATHERPP_SRC_PROVIDER_WEATHERDATA_H
#include <ctime>
#include <string>
using std::string;
/**
 * Class to represent the weather data returned from the provider.
 * Using cpprest's string_t to support cross platform, and prevent dealing with this when implementing a new provider.
 * Representation methods convert to an std::string to avoid dealing with this elsewhere.
 */
class WeatherData
{
  public:
    time_t timestamp;
    string city;
    string country;
    double latitude;
    double longitude;
    string units;
    string description;
    string iconName;
    int temp;
    int max;
    int min;
    int feelsLike;
    int humidity;
    int pressure;
    int cloudCoverage;
    int cloudCeiling;
    int visibility;
    time_t sunrise;
    time_t sunset;
    int windDegrees;
    double windSpeed;
    double windGustSpeed;
    std::string getShortRepresentation();
    static string getDegreesSymbol(const string &units);
};

#endif // WEATHERPP_SRC_PROVIDER_WEATHERDATA_H
