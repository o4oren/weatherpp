#include "OpenWeatherMap.h"

using namespace std;
using namespace web::http::client;
using namespace web::http;
using namespace weatherpp;
using namespace pplx;

namespace weatherpp
{
	task<void> OpenWeatherMap::httpGet(std::string url, string location, string apiKey)
	{
		uri_builder builder(U("http://api.openweathermap.org/"));
		builder.append_path(U("data/2.5/weather"));
		builder.set_query(U("q=" + location));
		builder.append_query("appid=" + apiKey);
		cout << builder.to_string() << endl;
		return http_client(U(builder.to_string()))
			.request(methods::GET)
			.then([=](const http_response& response)
			{
				cout << "Status code: " << response.status_code() << endl;
			  // Check the status code.
			  if (response.status_code() != 200)
			  {
				  throw runtime_error("Returned " + to_string(response.status_code()));
			  }

			  // Convert the response body to JSON object.
			  return response.extract_json();
			})
			.then([](const task<web::json::value>& previousTask)
			{
			  // Get the JSON value from the task and call the DisplayJSONValue method
			  try
			  {
				  web::json::value const & value = previousTask.get();
				  cout << value.serialize() << endl;
			  }
			  catch (http_exception const & e)
			  {
				  wcout << e.what() << endl;
			  }
			});
	}
}

