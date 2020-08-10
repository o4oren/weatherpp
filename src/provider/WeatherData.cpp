#include "WeatherData.h"
#include "../Const.h"
#include <iomanip>

using namespace std;
using namespace weatherpp;

string WeatherData::getShortRepresentation()
{
    string sunRiseString = asctime(localtime(&sunrise));
    string sunSetString = asctime(localtime(&sunset));

    std::ostringstream oss;
    oss << setprecision(2)
        << "Current weather at: " << city << ", " << country << "\n"
        << description << "\n"
        << "Cloud coverage: " << cloudCoverage << "%" << "\n"
        << "Temperature: " << temp << getDegreesSymbol(units) << "\n"
        << "Feels like: " << feelsLike << getDegreesSymbol(units) << "\n"
        << "Humidity: " << humidity << "%" << "\n"
        << "Pressure: " << pressure << " hPa" << "\n"
        << "Wind: " << windDegrees << " at " << windSpeed << WIND_SPEED_METRIC << "\n";
    if (windGustSpeed != 0)
    {
        oss << "Gusts: " << windGustSpeed << WIND_SPEED_METRIC << "\n";
    }
    oss << "Sunrise: " << sunRiseString
        << "Sunset: " << sunSetString;

    string s = oss.str();
    return s;
}

string WeatherData::getDegreesSymbol(const string &units)
{
    return units == "imperial" ? DEGREES_IMPERIAL : DEGREES_METRIC;
}