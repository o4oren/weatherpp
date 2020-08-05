#include "WeatherData.h"
using namespace std;

string WeatherData::get_short_presentation()
{
	// TODO investigate why this is working here, but not directly inline
	string sunRiseString = asctime(localtime(&sunrise));
	string sunSetString =  asctime(localtime(&sunset));


	string s = "Current weather at: "
		+ city + ", " + country + "\n"
		+ description + "\n"
		+ "cloud coverage: " + to_string(clouds) + "%\n"
		+ "Temperature: " + to_string(temp) + "\n"
		+ "Humidity: " + to_string(humidity) + "%\n"
		+ "Pressure: " + to_string(pressure) + "\n"
		+ "Feels like: " + to_string(feelsLike) + "\n"
		+ "Wind direction: " + to_string(windDegrees) + " at " + to_string(windSpeed) + "\n"
		+ "Sunrise: " + sunRiseString +
		+ "Sunset: " + sunSetString
	;
	return s;
}
