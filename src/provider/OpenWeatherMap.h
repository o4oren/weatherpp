#ifndef WEATHERPP_SRC_PROVIDER_OPENWEATHERMAP_H
#define WEATHERPP_SRC_PROVIDER_OPENWEATHERMAP_H

#pragma once
#include <string>
#include <pplx/pplxtasks.h>
#include <cpprest/json.h>
#include <cpprest/uri_builder.h>
#include <cpprest/http_client.h>
#include "IWeatherProvider.h"
using namespace web;
using std::string;

namespace weatherpp
{
	class OpenWeatherMap: public IWeatherProvider
	{
	public:
		WeatherData* getWeather(const string& url,
			const string& location,
			const string& apiKey,
			const string& units) override;
		~OpenWeatherMap() override {};
	private:
		WeatherData* generateWeatherData(json::value json);
	};
}

#endif //WEATHERPP_SRC_PROVIDER_OPENWEATHERMAP_H
