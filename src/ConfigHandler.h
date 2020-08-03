#ifndef WEATHERPP_SRC_CONFIGHANDLER_H
#define WEATHERPP_SRC_CONFIGHANDLER_H
#include <string>

namespace weatherpp
{
	class ConfigHandler
	{
	private:
		std::string mWeatherProviderName, mApiKey, mLocation;
		static constexpr const char* CONFIG_FILE_NAME = ".weatherpp";
		void parseArgs(int argc, char* argv[]);
		bool parseConfigFile(const std::string& cfgFile);
		bool createConfigFile(std::string& cfgFile, std::string& provider, std::string& apiKey);
		static std::string getConfigFilePath();

	public:
		/**
		 * Configures the app for weather fetching.
		 * @param argc - number of command line arguments.
		 * @param argv - command line args array.
		 * @return true if configuration is complete. false otherwise.
		 */
		bool configure(int argc, char* argv[]);
		bool isShowHelp = false;
		std::string getLocation() { return mLocation; };
		std::string getWeatherProviderName() { return mWeatherProviderName; };
		std::string getApiKey() { return mApiKey; };
	};
}

#endif //WEATHERPP_SRC_CONFIGHANDLER_H
