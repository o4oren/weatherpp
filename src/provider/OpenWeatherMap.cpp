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
WeatherData *OpenWeatherMap::getWeather(const string &url, const string &location, const string &apiKey,
                                        const string &units)
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
        })
        .get();
}

WeatherData *OpenWeatherMap::generateWeatherData(web::json::value json)
{
    auto *data = new WeatherData;
    data->units = to_utf8string(json.at(U("units")).as_string());
    data->city = to_utf8string(json.at(U("name")).as_string());
    data->country = to_utf8string(json.at(U("sys")).at(U("country")).as_string());
    data->temp = json.at(U("main")).at(U("temp")).as_integer();
    data->pressure = json.at(U("main")).at(U("pressure")).as_integer();
    data->humidity = json.at(U("main")).at(U("humidity")).as_integer();
    data->feelsLike = json.at(U("main")).at(U("feels_like")).as_integer();
    data->clouds = json.at(U("clouds")).at(U("all")).as_integer();
    data->windSpeed = json.at(U("wind")).at(U("speed")).as_double();
    data->windDegrees = json.at(U("wind")).at(U("deg")).as_integer();
    data->description = to_utf8string(json.at(U("weather")).as_array()[0].at(U("description")).as_string());
    data->sunrise = json.at(U("sys")).at(U("sunrise")).as_integer();
    data->sunset = json.at(U("sys")).at(U("sunset")).as_integer();
    return data;
}
} // namespace weatherpp
