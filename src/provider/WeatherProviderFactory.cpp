#include "WeatherProviderFactory.h"
#include "OpenWeatherMap.h"
using std::string;

namespace weatherpp
{
IWeatherProvider *WeatherProviderFactory::create(const string &weatherProviderName)
{
    if (weatherProviderName == "openweathermap")
    {
        return new OpenWeatherMap();
    }
    return nullptr;
}
} // namespace weatherpp
