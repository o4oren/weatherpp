#ifndef WEATHERPP_SRC_PROVIDER_WEATHERPROVIDERFACTORY_H
#define WEATHERPP_SRC_PROVIDER_WEATHERPROVIDERFACTORY_H
#include "IWeatherProvider.h"

namespace weatherpp
{
	class WeatherProviderFactory
	{
	public:
		static IWeatherProvider* create(const std::string&);
	private:
		std::vector<IWeatherProvider*> weatherProviders;
	};
}

#endif //WEATHERPP_SRC_PROVIDER_WEATHERPROVIDERFACTORY_H