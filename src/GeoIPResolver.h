#ifndef WEATHERPP_SRC_GEOIPRESOLVER_H
#define WEATHERPP_SRC_GEOIPRESOLVER_H
#include <string>
#include <string>
#include <pplx/pplxtasks.h>
#include <cpprest/json.h>
#include <cpprest/uri_builder.h>
#include <cpprest/http_client.h>
using std::string;
namespace weatherpp
{
	struct Location
	{
		string city;
		double lat;
		double lon;
		string country;
		string countryCode;
		string timezone;
		string isp;
		string query;
	};
	class GeoIPResolver
	{
	public:
		static pplx::task<Location> getLocationAsync();
	};
}


#endif //WEATHERPP_SRC_GEOIPRESOLVER_H
