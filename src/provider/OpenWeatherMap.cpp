#include "OpenWeatherMap.h"

using std::string;
using std::cout;
using std::runtime_error;
using std::to_string;
using std::endl;
using std::wcout;

using namespace web;
using namespace web::http::client;
using namespace web::http;
using namespace weatherpp;
using namespace pplx;

namespace weatherpp
{
	WeatherData* OpenWeatherMap::getWeather(const string& url,
		const string& location,
		const string& apiKey,
		const string& units)
	{
		uri_builder builder(U("http://api.openweathermap.org/"));
		builder.append_path(U("data/2.5/weather"))
			.set_query(U("q=" + uri::encode_data_string(location)))
			.append_query("appid=" + apiKey)
			.append_query("units=" + units);
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
			.then([=](const task<json::value>& previousTask)
			{
			  json::value const &value = previousTask.get();
			  auto newJson = value;
			  newJson["units"] = json::value::string(U(units));
			  WeatherData* data = generateWeatherData(newJson);
			  return data;
			}).get();
	}

		WeatherData* OpenWeatherMap::generateWeatherData(web::json::value json)
		{
			auto* data = new WeatherData;
			// cout << json.serialize() << endl; //print json body
			data->units = json.at("units").as_string();
			data->city = json.at("name").as_string();
			data->country = json.at("sys").at("country").as_string();
			data->temp = json.at("main").at("temp").as_integer();
			data->pressure = json.at("main").at("pressure").as_integer();
			data->humidity = json.at("main").at("humidity").as_integer();
			data->feelsLike = json.at("main").at("feels_like").as_integer();
			data->clouds = json.at("clouds").at("all").as_integer();
			data->windSpeed = json.at("wind").at("speed").as_double();
			data->windDegrees = json.at("wind").at("deg").as_integer();
			data->description = json.at("weather").as_array()[0].at("description").as_string();
			data->sunrise = json.at("sys").at("sunrise").as_integer();
			data->sunset = json.at("sys").at("sunset").as_integer();
			return data;
		}

}

