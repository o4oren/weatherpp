#include "WeatherData.h"
#include "../Const.h"
#include <cpprest/json.h>

using namespace std;
using namespace utility::conversions;
using namespace weatherpp;

string WeatherData::getShortRepresentation()
{
    // TODO investigate why this is working here, but not directly inline
    string sunRiseString = asctime(localtime(&sunrise));
    string sunSetString = asctime(localtime(&sunset));

    string s = "Current weather at: " + city + ", " + country + "\n" + description + "\n" +
               "cloud coverage: " + to_string(clouds) + "%\n" + "Temperature: " + to_string(temp) +
               getDegreesSymbol(units) + "\n" + "Humidity: " + to_string(humidity) + "%\n" +
               "Pressure: " + to_string(pressure) + " hPa\n" + "Feels like: " + to_string(feelsLike) +
               getDegreesSymbol(units) + "\n" + "Wind direction: " + to_string(windDegrees) + " at " +
               to_string(windSpeed) + " m/sec\n" + "Sunrise: " + sunRiseString + +"Sunset: " + sunSetString;
    return s;
}

string WeatherData::getDegreesSymbol(const string &units)
{
    return DEGREES_SYMBOL + (units == "imperial" ? DEGREES_IMPERIAL : DEGREES_METRIC);
}