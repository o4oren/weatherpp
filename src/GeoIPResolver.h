#ifndef WEATHERPP_SRC_GEOIPRESOLVER_H
#define WEATHERPP_SRC_GEOIPRESOLVER_H
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/uri_builder.h>
#include <pplx/pplxtasks.h>
#include <string>
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
} // namespace weatherpp

#endif // WEATHERPP_SRC_GEOIPRESOLVER_H
