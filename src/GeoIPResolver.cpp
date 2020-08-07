#include "GeoIPResolver.h"
using std::string;
using std::cout;
using std::runtime_error;
using std::to_string;
using std::endl;
using std::wcout;
using namespace web::http;

using namespace web::http::client;
using namespace web::http;
using namespace pplx;

namespace weatherpp
{
	task<weatherpp::Location> GeoIPResolver::getLocationAsync()
	{
		return http_client(U("http://ip-api.com/json/"))
			.request(methods::GET)
			.then([](const http_response& response)
			{
			  if (response.status_code() != 200)
			  {
				  throw runtime_error("Returned " + to_string(response.status_code()));
			  }
			  return response.extract_json();
			})
			.then([](const task<web::json::value>& previousTask)
			{
			  web::json::value const& value = previousTask.get();
			  Location location;
			  location.city = value.at("city").as_string();
			  return location;
			});
	}
}