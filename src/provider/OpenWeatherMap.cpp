#include "OpenWeatherMap.h"

using namespace web;
using namespace web::http::client;
using namespace web::http;
using namespace weatherpp;
using namespace pplx;
using namespace utility::conversions;
using namespace std;

namespace weatherpp
{
/*
 * With open weather map we use separate apis calls for current weather, and for 5 day/3 hour forecast
 * due to their limit on forecast apis for paid plans.
 */
WeatherData *OpenWeatherMap::getWeather(const string &url, const string &location, const string &apiKey,
                                        const string &units)
{
    auto currentWeatherTask = getCurrentWeather(url, location, apiKey, units);
    auto forecastTask = getForecast(url, location, apiKey, units);
    auto weatherData = currentWeatherTask.get();
    vector<WeatherData*> forecastData = forecastTask.get();
    weatherData->forecast.assign(forecastData.begin(), forecastData.end());
    // Open weather map returns all data in GMT. We need to fix it for local tz.
    weatherData->applyTzOffset(weatherData->tzOffset);
    return weatherData;
}

task<WeatherData*> OpenWeatherMap::getCurrentWeather(const string &url, const string &location,
    const string &apiKey, const string &units)
{
    uri_builder builder(U("http://api.openweathermap.org/"));
    builder.append_path(U("data/2.5/weather"))
        .set_query(U("q=") + (uri::encode_data_string(to_string_t(location))))
        .append_query(to_string_t("appid=" + apiKey))
        .append_query(to_string_t("units=" + units));
    return http_client(builder.to_string())
        .request(methods::GET)
        .then([=](const http_response &response) {
          if (response.status_code() != 200)
          {
              throw runtime_error("Returned " + to_string(response.status_code()));
          }
          return response.extract_json();
        })
        .then([=](const task<json::value> &previousTask) {
          json::value const &value = previousTask.get();
          auto newJson = value;
          newJson[U("units")] = json::value::string(to_string_t(units));
          WeatherData *data = generateWeatherData(newJson);
          return data;
        });
}

task<vector<WeatherData*>> OpenWeatherMap::getForecast(const string &url, const string &location, const string &apiKey,
    const string &units)
{
    uri_builder builder(U("http://api.openweathermap.org/"));
    builder.append_path(U("data/2.5/forecast"))
        .set_query(U("q=") + (uri::encode_data_string(to_string_t(location))))
        .append_query(to_string_t("appid=" + apiKey))
        .append_query(to_string_t("units=" + units));
    return http_client(builder.to_string())
        .request(methods::GET)
        .then([=](const http_response &response) {
          if (response.status_code() != 200)
          {
              throw runtime_error("Returned " + to_string(response.status_code()));
          }
          return response.extract_json();
        })
        .then([=](const task<json::value> &jsonTaskResult) {
          json::value const &value = jsonTaskResult.get();
          vector<WeatherData*> forcastVector;
          for (json::value listItem : value.at(U("list")).as_array())
          {
              WeatherData *data = generateWeatherData(listItem, false);
              forcastVector.push_back(data);
          }
          return forcastVector;
        });
}

WeatherData *OpenWeatherMap::generateWeatherData(web::json::value json, bool isCurrent)
{
    /*
     * Due to cpprestsdk's use of string_t we need to convert every json string value to utf_8 string, so it is
     * parsed correctly into a standrd string on the WeatherData object.
     */
    auto *data = new WeatherData;
    if (isCurrent) data->units = to_utf8string(json.at(U("units")).as_string());
    if (isCurrent) data->city = to_utf8string(json.at(U("name")).as_string());
    if (isCurrent)  data->country = to_utf8string(json.at(U("sys")).at(U("country")).as_string());
    data->tzOffset = json.has_field(U("timezone")) ? json.at(U("timezone")).as_integer() : 0;
    data->timestamp = json.at(U("dt")).as_integer();
    data->temp = json.at(U("main")).at(U("temp")).as_integer();
    data->pressure = json.at(U("main")).at(U("pressure")).as_integer();
    data->humidity = json.at(U("main")).at(U("humidity")).as_integer();
    data->visibility = json.at(U("visibility")).as_integer();
    data->feelsLike = json.at(U("main")).at(U("feels_like")).as_integer();
    data->cloudCoverage = json.at(U("clouds")).at(U("all")).as_integer();
    data->windSpeed = json.at(U("wind")).at(U("speed")).as_double();
    data->windDegrees = json.at(U("wind")).at(U("deg")).as_integer();
    data->windGustSpeed = json.at(U("wind")).has_field(U("gust")) ? json.at(U("wind")).at(U("gust")).as_double() : 0;
	data->description = to_utf8string(json.at(U("weather")).as_array()[0].at(U("description")).as_string());
    data->iconName = to_utf8string(json.at(U("weather")).as_array()[0].at(U("main")).as_string());
    if (isCurrent) data->sunrise = json.at(U("sys")).at(U("sunrise")).as_integer();
    if (isCurrent) data->sunset = json.at(U("sys")).at(U("sunset")).as_integer();
    return data;
}
} // namespace weatherpp
