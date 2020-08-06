#ifndef WEATHERPP_SRC_PROVIDER_IWEATHERPROVIDER_H
#define WEATHERPP_SRC_PROVIDER_IWEATHERPROVIDER_H

#include <pplx/pplxtasks.h>
#include <cpprest/json.h>
#include "WeatherData.h"

namespace weatherpp
{
	class IWeatherProvider
	{
	public:
		virtual WeatherData* getWeather(const std::string& url,
			const std::string& location,
			const std::string& apiKey,
			const std::string& units) = 0;
		virtual ~IWeatherProvider() = default;;
	private:
		virtual WeatherData* generateWeatherData(web::json::value json) = 0;
	};
}
#endif //WEATHERPP_SRC_PROVIDER_IWEATHERPROVIDER_H
