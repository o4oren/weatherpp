#ifndef WEATHERPP_SRC_CONFIGHANDLER_H
#define WEATHERPP_SRC_CONFIGHANDLER_H
#include <string>
using std::string;

namespace weatherpp
{
	struct Configuration
	{
		string weatherProvider;
		string apiKey;
		string location;
		string defaultLocation;
		string units;
		bool isSaveConfig = false;
	};

	class ConfigHandler
	{
	private:
		static constexpr const char* CONFIG_FILE_NAME = ".weatherpp";
		void parseArgs(int argc, char* argv[]);
		bool parseConfigFile(const string& cfgFile);
		string getConfigFilePath();
		Configuration configuration;

	public:
		/**
		 * Configures the app for weather fetching.
		 * @param argc - number of command line arguments.
		 * @param argv - command line args array.
		 * @return true if configuration is complete. false otherwise.
		 */
		bool configure(int argc, char* argv[]);
		bool isShowHelp = false;
		const Configuration& getConfiguration();
		bool createConfigFile(const Configuration &configuration);
		const string os =
		#ifdef _WIN32
			"windows";
		#else
			"unix";
		#endif
	};
}

#endif //WEATHERPP_SRC_CONFIGHANDLER_H
