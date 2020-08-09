#include "GeoIPResolver.h"
using std::cout;
using std::endl;
using std::runtime_error;
using std::string;
using std::to_string;
using std::wcout;
using namespace web::http;

using namespace web::http::client;
using namespace web::http;
using namespace pplx;
using namespace utility::conversions;

namespace weatherpp
{
task<weatherpp::Location> GeoIPResolver::getLocationAsync()
{
    return http_client(U("http://ip-api.com/json/"))
        .request(methods::GET)
        .then([](const http_response &response) {
            if (response.status_code() != 200)
            {
                throw runtime_error("Geo IP Returned " + to_string(response.status_code()));
            }
            return response.extract_json();
        })
        .then([](const task<web::json::value> &previousTask) {
            web::json::value const &value = previousTask.get();
            Location location;
            location.city = to_utf8string(value.at(U("city")).as_string());
            return location;
        });
}
} // namespace weatherpp