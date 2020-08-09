#ifndef WEATHERPP_SRC_PROVIDER_WEATHERDATA_H
#define WEATHERPP_SRC_PROVIDER_WEATHERDATA_H
#include <ctime>
#include <string>
using std::string;

class WeatherData
{
  public:
    string units;
    int clouds;
    double latitude;
    double longitude;
    time_t timestamp;
    string city;
    string country;
    int humidity;
    int pressure;
    int temp;
    int max;
    int min;
    int feelsLike;
    int visibility;
    time_t sunrise;
    time_t sunset;
    string description;
    int windDegrees;
    double windSpeed;
    string getShortRepresentation();
    static string getDegreesSymbol(const string &units);
};

#endif // WEATHERPP_SRC_PROVIDER_WEATHERDATA_H
