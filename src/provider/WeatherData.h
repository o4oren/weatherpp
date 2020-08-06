#ifndef WEATHERPP_SRC_PROVIDER_WEATHERDATA_H
#define WEATHERPP_SRC_PROVIDER_WEATHERDATA_H
#include <string>
#include <ctime>

class WeatherData
{
public:
	int clouds;
	double latitude;
	double longitude;
	time_t timestamp;
	std::string city;
	std::string country;
	int humidity;
	int pressure;
	int temp;
	int feelsLike;
	int visibility;
	time_t sunrise;
	time_t sunset;
	std::string description;
	int windDegrees;
	double windSpeed;
	std::string getShortRepresentation();
};

#endif //WEATHERPP_SRC_PROVIDER_WEATHERDATA_H
