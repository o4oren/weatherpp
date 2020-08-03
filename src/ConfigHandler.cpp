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
		bool isCfgParsed = parseConfigFile(cfgFile);
		if (!isCfgParsed && !mWeatherProviderName.empty() && !mApiKey.empty())
		{
			createConfigFile(cfgFile, mWeatherProviderName, mApiKey);
		}

		if (!mWeatherProviderName.empty() && !mApiKey.empty())
		{
			return true;
		}
		return false;
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
					mWeatherProviderName = argv[++i];
				}
			}
			else if ((arg == "-a") || (arg == "--apikey"))
			{
				if (i + 1 < argc)
				{
					mApiKey = argv[++i];
				}
			}
			else
			{
				if (mLocation.empty())
				{
					mLocation = argv[i];
				}
				else
				{
					mLocation.append(" ").append(argv[i]);
				}
			}
		}
	}

	/**
	 * @param cfgFile - reference to string denoting the path tothe cfg file;
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

				if (key == "provider" && mWeatherProviderName.empty())
				{
					mWeatherProviderName = value;
				}
				if (key == "apikey" && mApiKey.empty())
				{
					mApiKey = value;
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
	bool ConfigHandler::createConfigFile(string& cfgFile, string& provider, string& apiKey)
	{
		ofstream out(cfgFile);
		out << "provider=" << provider << endl;
		out << "apikey=" << apiKey << endl;
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
}
