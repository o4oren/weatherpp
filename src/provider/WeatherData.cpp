#include "WeatherData.h"
using namespace std;

string WeatherData::getShortRepresentation()
{
	// TODO investigate why this is working here, but not directly inline
	string sunRiseString = asctime(localtime(&sunrise));
	string sunSetString =  asctime(localtime(&sunset));

	string s = "Current weather at: "
		+ city + ", " + country + "\n"
		+ description + "\n"
		+ "cloud coverage: " + to_string(clouds) + "%\n"
		+ "Temperature: " + to_string(temp) + getDegreesSymbol(units) + "\n"
		+ "Humidity: " + to_string(humidity) + "%\n"
		+ "Pressure: " + to_string(pressure) + " hPa\n"
		+ "Feels like: " + to_string(feelsLike) + getDegreesSymbol(units) + "\n"
		+ "Wind direction: " + to_string(windDegrees) + " at " + to_string(windSpeed) + " m/sec\n"
		+ "Sunrise: " + sunRiseString +
		+ "Sunset: " + sunSetString
	;
	return s;
}

const string WeatherData::getDegreesSymbol(string units)
{
	string s = units == "imperial" ? "\u2109" :  "\u2103";
	return s;
}


