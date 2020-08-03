#include <string>
#include <iostream>
#include "ConfigHandler.h"
#include "provider/OpenWeatherMap.h"

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
			cout << "location " << configHandler.getLocation() << endl;
			cout << "provider: " << configHandler.getWeatherProviderName() << endl;
			cout << "api-key: " << configHandler.getApiKey() << endl;

			OpenWeatherMap m;
			m.httpGet("", configHandler.getLocation(), configHandler.getApiKey()).wait();
		}
	}
	else
	{
		showHelp(argv[0]);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
