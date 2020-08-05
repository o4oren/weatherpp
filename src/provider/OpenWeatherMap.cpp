#include "OpenWeatherMap.h"

using std::string;
using std::cout;
using std::runtime_error;
using std::to_string;
using std::endl;
using std::wcout;

using namespace web::http::client;
using namespace web::http;
using namespace weatherpp;
using namespace pplx;

namespace weatherpp
{
	WeatherData* OpenWeatherMap::getWeather(const string& url, const string& apiKey)
	{
		return OpenWeatherMap::getWeather(url, "london", apiKey);
	}
	WeatherData* OpenWeatherMap::getWeather(const string& url, const string& location, const string& apiKey)
	{
		uri_builder builder(U("http://api.openweathermap.org/"));
		builder.append_path(U("data/2.5/weather"))
		.set_query(U("q=" + web::uri::encode_data_string(location)))
		.append_query("appid=" + apiKey)
		.append_query("units=metric");
		cout << builder.to_string();
		return http_client(U(builder.to_string()))
			.request(methods::GET)
			.then([=](const http_response& response)
			{
			  if (response.status_code() != 200)
			  {
				  throw runtime_error("Returned " + to_string(response.status_code()));
			  }
			  return response.extract_json();
			})
			  .then([=](const task<web::json::value>& previousTask)
			  {
				web::json::value const& value = previousTask.get();
				WeatherData* data = generateWeatherData(value);
				return data;
			  }).get();
			}

		WeatherData* OpenWeatherMap::generateWeatherData(web::json::value json)
		{
			auto* data = new WeatherData;
			// cout << json.serialize() << endl; //print json body
			data->city = json.at("name").as_string();
			data->country = json.at("sys").at("country").as_string();
			data->temp = json.at("main").at("temp").as_double();
			data->pressure = json.at("main").at("pressure").as_integer();
			data->humidity = json.at("main").at("humidity").as_double();
			data->feelsLike = json.at("main").at("feels_like").as_double();
			data->clouds = json.at("clouds").at("all").as_integer();
			data->windSpeed = json.at("wind").at("speed").as_double();
			data->windDegrees = json.at("wind").at("deg").as_integer();
			data->description = json.at("weather").as_array()[0].at("description").as_string();
			data->sunrise = json.at("sys").at("sunrise").as_integer();
			data->sunset = json.at("sys").at("sunset").as_integer();
			return data;
		}
	}

