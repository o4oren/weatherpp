#include <string>
#include <iostream>
#include "ConfigHandler.h"
#include "provider/WeatherProviderFactory.h"

using namespace std;
using namespace weatherpp;

void showHelp(char* name)
{
	cout << "Usage: " << name << " [option(s)] [LOCATION]\n"
		 << "Options:\n"
		 << "\t-h,--help\t\tShow this help message\n"
		 << "\t-p,--provider PROVIDER\tSpecify the weather provider name"
		 << "\t-a,--apikey API-KEY\tSpecify the weather provider's API key"
		 << endl;
}

int main(int argc, char* argv[])
{
	ConfigHandler configHandler;
	if(configHandler.configure(argc, argv))
	{
		if (configHandler.isShowHelp)
		{
			showHelp(argv[0]);
		}
		else
		{
			IWeatherProvider* provider = WeatherProviderFactory::create("openweathermap");
			if (provider)
			{
				auto weatherData = provider->getWeather("", configHandler.getLocation(), configHandler.getApiKey());
				cout << weatherData->get_short_presentation() << endl;
				delete weatherData;
			}
			provider = nullptr;
			delete provider;
		}
	}
	else
	{
		showHelp(argv[0]);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
