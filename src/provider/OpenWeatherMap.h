#ifndef WEATHERPP_SRC_PROVIDER_OPENWEATHERMAP_H
#define WEATHERPP_SRC_PROVIDER_OPENWEATHERMAP_H

#pragma once
#include <string>
#include <pplx/pplxtasks.h>
#include <cpprest/json.h>
#include <cpprest/uri_builder.h>
#include <cpprest/http_client.h>
#include "IWeatherProvider.h"

using std::string;

namespace weatherpp
{
	class OpenWeatherMap: public IWeatherProvider
	{
	public:
		WeatherData* getWeather(const string& url, const string& apiKey) override;
		WeatherData* getWeather(const string& url, const string& location, const string& apiKey) override;
		virtual ~OpenWeatherMap() {};
	private:
		WeatherData* generateWeatherData(web::json::value json);
	};
}

#endif //WEATHERPP_SRC_PROVIDER_OPENWEATHERMAP_H
