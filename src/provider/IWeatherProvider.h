#ifndef WEATHERPP_SRC_PROVIDER_IWEATHERPROVIDER_H
#define WEATHERPP_SRC_PROVIDER_IWEATHERPROVIDER_H

#include "WeatherData.h"
#include <cpprest/json.h>
#include <pplx/pplxtasks.h>

namespace weatherpp
{
class IWeatherProvider
{
  public:
    virtual WeatherData *getWeather(const std::string &url, const std::string &location, const std::string &apiKey,
                                    const std::string &units) = 0;
    virtual ~IWeatherProvider() = default;
    ;

  private:
    virtual WeatherData *generateWeatherData(web::json::value json) = 0;
};
} // namespace weatherpp
#endif // WEATHERPP_SRC_PROVIDER_IWEATHERPROVIDER_H
