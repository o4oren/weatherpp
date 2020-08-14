#ifndef WEATHERPP_SRC_PROVIDER_OPENWEATHERMAP_H
#define WEATHERPP_SRC_PROVIDER_OPENWEATHERMAP_H

#pragma once
#include "IWeatherProvider.h"
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/uri_builder.h>
#include <pplx/pplxtasks.h>
#include <string>
using namespace web;
using std::string;

namespace weatherpp
{
class OpenWeatherMap : public IWeatherProvider
{
  public:
    WeatherData *getWeather(const string &jsonTaskResult, const string &location, const string &apiKey,
                            const string &units) override;
    ~OpenWeatherMap() override= default;

  private:
    WeatherData *generateWeatherData(json::value json, bool isCurrent = true) override;
    pplx::task<WeatherData*> getCurrentWeather(const string &url, const string &location, const string &apiKey,
        const string &units);
    pplx::task<std::vector<WeatherData*>> getForecast(const string &url, const string &location, const string &apiKey,
        const string &units);
};
} // namespace weatherpp

#endif // WEATHERPP_SRC_PROVIDER_OPENWEATHERMAP_H
