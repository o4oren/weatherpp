#include "WeatherData.h"
#include "../Const.h"
#include <cpprest/json.h>

using namespace std;
using namespace utility::conversions;
using namespace weatherpp;

string WeatherData::getShortRepresentation()
{
    const string_t END_LINE = U("\n");
    string_t sunRiseString = to_string_t(asctime(localtime(&sunrise)));
    string_t sunSetString = to_string_t(asctime(localtime(&sunset)));

    utility::ostringstream_t oss;
    oss << U("Current weather at: ") << city << U(", ") << country << END_LINE
        << description << END_LINE
        << U("cloud coverage: ") << clouds << U("%\n")
        << U("Temperature: ") << temp << getDegreesSymbol(units) << END_LINE
        << U("Feels like: ") << feelsLike << getDegreesSymbol(units) << END_LINE
        << U("Humidity: ") << humidity << U("%") << END_LINE
        << U("Pressure: ") << pressure << U(" hPa") << END_LINE
        << U("Wind direction: ") << windDegrees << U(" at ") << windSpeed << U(" m/sec") << END_LINE
        << U("Sunrise: ") << sunRiseString
        << U("Sunset: ") << sunSetString;

    string_t s = oss.str();
    return to_utf8string(s);
}

string_t WeatherData::getDegreesSymbol(const string_t &units)
{
    return units == U("imperial") ? to_string_t(DEGREES_IMPERIAL) : to_string_t(DEGREES_METRIC);
}