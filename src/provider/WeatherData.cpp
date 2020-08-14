#include "WeatherData.h"
#include "../Const.h"
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace weatherpp;

string WeatherData::getShortRepresentation()
{
    string sunRiseString = asctime(gmtime(&sunrise));
    string sunSetString = asctime(gmtime(&sunset));

    std::ostringstream oss;
    oss << setprecision(2) << "Current weather at: " << city << ", " << country << "\n"
        << description << "\n"
        << "Cloud coverage: " << cloudCoverage << "%"
        << "\n"
        << "Visibility: " << visibility << "m"
        << "\n"
        << "Temperature: " << temp << getDegreesSymbol(units) << "\n"
        << "Feels like: " << feelsLike << getDegreesSymbol(units) << "\n"
        << "Humidity: " << humidity << "%"
        << "\n"
        << "Pressure: " << pressure << " hPa"
        << "\n"
        << "Wind: " << windDegrees << " at " << windSpeed << getWindSpeedUnits(units) << "\n";
    if (windGustSpeed != 0)
    {
        oss << "Gusts: " << windGustSpeed << " " << getWindSpeedUnits(units) << "\n";
    }
    oss << "Sunrise: " << sunRiseString << "Sunset: " << sunSetString;

    string s = oss.str();
    return s;
}

string WeatherData::getShortForecastRepresentation()
{
    if (forecast.empty())
    {
        return "Forecast data doesn't exist.";
    }
    std::ostringstream oss;
    oss << setprecision(2);
    auto time = gmtime(&forecast[0]->timestamp);
    int yday = time->tm_yday;
    int year = time->tm_year;
    char forecastDay[20];
    strftime(forecastDay, sizeof(forecastDay), "%a, %x", time);
    oss << "Forecast for " << forecastDay << ":\n";
    for (auto it = forecast.begin(); it < forecast.end(); ++it)
    {
        if(yday != gmtime(&(*it)->timestamp)->tm_yday
            || year != gmtime(&(*it)->timestamp)->tm_year)
        {
            char forecastDay[20];
            strftime(forecastDay, sizeof(forecastDay), "%a, %x", gmtime(&(*it)->timestamp));
            oss << "\nForecast for " << forecastDay << ":\n";
            yday = gmtime(&(*it)->timestamp)->tm_yday;
            year = gmtime(&(*it)->timestamp)->tm_year;
        }
        else
        {
            char timeOfDay[8];
            strftime(timeOfDay, sizeof(timeOfDay), "%H:%M", gmtime(&(*it)->timestamp));
            oss << timeOfDay << " "
                << (*it)->description << ", Temp: " << (*it)->temp << getDegreesSymbol(units)
                << ", Wind: " << windDegrees << " at " << windSpeed << getWindSpeedUnits(units) << "\n";
        }
    }

    string s = oss.str();
    return s;
}

string WeatherData::getDegreesSymbol(const string &units)
{
    return units == "imperial" ? DEGREES_IMPERIAL : DEGREES_METRIC;
}
string WeatherData::getWindSpeedUnits(const string &units)
{
    return units == "metric" ? WIND_SPEED_METRIC : WIND_SPEED_IMPERIAL;
}
void WeatherData::applyTzOffset(long offset)
{
    timestamp += offset;
    sunrise += offset;
    sunset += offset;
    for (auto data : forecast)
    {
        data->timestamp += offset;
    }
}
