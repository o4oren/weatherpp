#include "ConfigHandler.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
using namespace weatherpp;

namespace weatherpp
{
	bool ConfigHandler::configure(int argc, char** argv)
	{
		parseArgs(argc, argv);
		string cfgFile = getConfigFilePath();
		parseConfigFile(cfgFile);
		// config is valid if provider and api key are set
		return !configuration.weatherProvider.empty() && !configuration.apiKey.empty();
	}

	void ConfigHandler::parseArgs(int argc, char** argv)
	{
		for (int i = 1; i < argc; ++i)
		{
			string arg = argv[i];
			if ((arg == "-h") || (arg == "--help"))
			{
				isShowHelp = true;
			}
			else if ((arg == "-p") || (arg == "--provider"))
			{
				if (i + 1 < argc)
				{
					configuration.weatherProvider = argv[++i];
				}
			}
			else if ((arg == "-a") || (arg == "--apikey"))
			{
				if (i + 1 < argc)
				{
					configuration.apiKey = argv[++i];
				}
			}
			else if ((arg == "-u") || (arg == "--units"))
			{
				if (i + 1 < argc)
				{
					string unitsString = argv[++i];
					configuration.units = unitsString == "imperial" ? "imperial" : "metric";
				}
			}
			else if ((arg == "-d") || (arg == "--default-location"))
			{
				if (i + 1 < argc)
				{
					configuration.defaultLocation = argv[++i];
				}
			}
			else if ((arg == "-s") || (arg == "--save-configuration"))
			{
				configuration.isSaveConfig = true;
			}
			else
			{
				if (configuration.location.empty())
				{
					configuration.location = argv[i];
				}
				else
				{
					configuration.location.append(" ").append(argv[i]);
				}
			}
		}
	}

	/**
	 * @param cfgFile - reference to string denoting the path to the cfg file;
	 * @return true if successfully read configuration.
	 */
	bool ConfigHandler::parseConfigFile(const string& cfgFile)
	{
		ifstream in(cfgFile);
		if(in.good())
		{
			cout << "Config file found: " << cfgFile << endl;
			string line;
			string delimiter = "=";
			while(getline(in, line))
			{
				auto pos = line.find(delimiter);
				string key = line.substr(0, pos);
				line.erase(0, pos + 1);
				string value = line;

				if (configuration.weatherProvider.empty() && key == "provider")
				{
					configuration.weatherProvider = value;
				}
				if (configuration.apiKey.empty() && key == "apikey")
				{
					configuration.apiKey = value;
				}
				if (key == "defaultLocation")
				{
					configuration.defaultLocation = value;
				}
				if (configuration.units.empty() && key == "units")
				{
					configuration.units = value;
				}
			}
			return true;
		}
		else
		{
			cerr << "Config file not found at: " << cfgFile << endl;
			return false;
		}
	}

	/**
	 *
	 * @param cfgFile path to config file
	 * @param provider weather provider name
	 * @param apiKey weather provider api key
	 * @return true if successfully written config
	 */
	bool ConfigHandler::createConfigFile(const Configuration &config)
	{
		ofstream out(getConfigFilePath());
		out << "provider=" << config.weatherProvider << endl;
		out << "apikey=" << config.apiKey << endl;
		out << "defaultLocation=" << config.defaultLocation << endl;
		if (!config.units.empty())
			out << "units=" << config.units << endl;

		if (out.good()) {
			return true;
		}
		return false;
	}

	string ConfigHandler::getConfigFilePath()
	{
		// TODO make platform independent
		string homeDir = getenv("HOME");
		string pathSeperator = "/";
		return homeDir + pathSeperator + CONFIG_FILE_NAME;
	}
	const Configuration& ConfigHandler::getConfiguration()
	{
		return configuration;
	}
}
