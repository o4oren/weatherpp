#include "ConfigHandler.h"
#include "GeoIPResolver.h"
#include "provider/WeatherProviderFactory.h"

using namespace std;
using namespace weatherpp;

void showHelp(const char *name)
{
    cout << "Usage: " << name << " [option(s)] [LOCATION]\n"
         << "Options:\n"
         << "\t-h, --help\t\tShow this help message\n"
         << "\t-p, --provider <PROVIDER>\tSpecify the weather provider name\n"
         << "\t-a, --apikey <API-KEY>\t\tSpecify the weather provider's API key\n"
         << "\t-u, --units <UNITS>\t\tSpecify \"metric\" or \"imperial\" - "
            "metric is set by default\n"
         << "\t-s, --save-configuration \tSave passed arguments in configuration "
            "file\n"

         << endl;
}

int main(int argc, char *argv[])
{
    auto currentLocation = GeoIPResolver::getLocationAsync();
    ConfigHandler configHandler;
    if (configHandler.configure(argc, argv))
    {
        if (configHandler.isShowHelp)
        {
            showHelp(argv[0]);
        }
        else
        {
            auto configuration = configHandler.getConfiguration();
            if (configuration.isSaveConfig)
            {
                configHandler.createConfigFile(configuration);
            }
            IWeatherProvider *provider = WeatherProviderFactory::create(configuration.weatherProvider);
            if (provider)
            {
                // TODO resolve default location as needed
                auto location = !configuration.location.empty() ? configuration.location : currentLocation.get().city;
                auto weatherData = provider->getWeather("", location, configuration.apiKey, configuration.units);
                cout << weatherData->getShortRepresentation() << endl;
                cout << weatherData-> getShortForecastRepresentation() << endl;
                delete weatherData;
            }
            // TODO handle error if provider is not resolved
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
