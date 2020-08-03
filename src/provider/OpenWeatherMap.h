//
// Created by oren on 03/08/2020.
//

#ifndef WEATHERPP_SRC_PROVIDER_OPENWEATHERMAP_H
#define WEATHERPP_SRC_PROVIDER_OPENWEATHERMAP_H

#pragma once
#include <string>
#include <pplx/pplxtasks.h>
#include <cpprest/json.h>
#include <cpprest/uri_builder.h>
#include <cpprest/http_client.h>

namespace weatherpp {
	class OpenWeatherMap
	{
	public:
		pplx::task<void> httpGet(std::string url);

		pplx::task<void> httpGet(std::string url, std::string location, std::string apiKey);
	};
}

#endif //WEATHERPP_SRC_PROVIDER_OPENWEATHERMAP_H
