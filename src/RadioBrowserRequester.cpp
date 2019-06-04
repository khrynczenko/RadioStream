#include "../include/RadioBrowserRequester.hpp"
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>

std::vector<nlohmann::json> RadioBrowserRequester::request_stations(std::string_view search_phrase, std::string_view country, std::string_view language, OrderBy order)
{
    std::vector<std::pair<std::string, std::string>> request_parameters;
    const Poco::URI advanced_search_uri("/webservice/json/stations/search");
    std::string order_value = [order]()
    {
        switch(order)
        {
        case OrderBy::ClickCount: return "clickcount";
        case OrderBy::ClickTrend: return "clicktrend";
        case OrderBy::Votes:      return "votes";
        }
    }();
    if (country != "Any") request_parameters.emplace_back("country", country);
    if (language != "Any") request_parameters.emplace_back("language", language);
    request_parameters.emplace_back("name", search_phrase);
    request_parameters.emplace_back("limit", std::to_string(limit_));
    request_parameters.emplace_back("order", order_value);
    request_parameters.emplace_back("reverse", "true");
    auto response = send_arbitrary_request(advanced_search_uri, request_parameters);
    return response["response"].get<std::vector<nlohmann::json>>();
}

std::vector<nlohmann::json> RadioBrowserRequester::request_countries()
{
    const Poco::URI countries_uri("/webservice/json/countries");
    auto response = send_arbitrary_request(countries_uri, {});
    return response["response"].get<std::vector<nlohmann::json>>();
}

std::vector<nlohmann::json> RadioBrowserRequester::request_languages()
{
    const Poco::URI countries_uri("/webservice/json/languages");
    auto response = send_arbitrary_request(countries_uri, {});
    return response["response"].get<std::vector<nlohmann::json>>();
}


std::string RadioBrowserRequester::correct_json_response(std::string response) const
{
    //radio-browser API returns not valid JSON object which makes in unparsable by nlohmann library,
    //this little change corrects it.
    response.push_back('}');
    return "{ \"response\" : " + response;
}

nlohmann::json RadioBrowserRequester::send_arbitrary_request(const Poco::URI &request_uri,
                                                             Parameters request_parameters)
{
    Poco::Net::HTTPRequest request("POST", request_uri.toString());
    std::string request_body;
    for(const auto& [parameter_name, parameter_value] : request_parameters)
    {
        request_body.append(parameter_name + '=' + parameter_value + '&');
    }
    request.setContentType("application/x-www-form-urlencoded");
    request.setContentLength(request_body.size());
    session_.sendRequest(request) << request_body;
    Poco::Net::HTTPResponse response;
    auto& response_stream = session_.receiveResponse(response);
    std::stringstream response_string;
    Poco::StreamCopier::copyStream(response_stream, response_string);
    const auto serialized_json = correct_json_response(response_string.str());
    nlohmann::json j_response = nlohmann::json::parse(serialized_json);
    return j_response;

}

RadioBrowserRequester::RadioBrowserRequester(unsigned short int search_stations_limit)
    : limit_(search_stations_limit)
{

}

std::vector<Station> parse_stations_jsons(const std::vector<nlohmann::json>& stations_jsons)
{
    std::vector<Station> stations;
    stations.reserve(stations_jsons.size());
    for(const auto& station_json : stations_jsons)
    {
        if(std::stoi(station_json["lastcheckok"].get<std::string>()) == 1)
        {
            stations.emplace_back(station_json["name"].get<std::string>(),
                                  station_json["url"].get<std::string>(),
                                  station_json["country"].get<std::string>(),
                                  station_json["language"].get<std::string>(),
                                  station_json["codec"].get<std::string>(),
                                  station_json["bitrate"].get<std::string>() + std::string(" kbps"),
                                  station_json["tags"].get<std::string>());
        }
    }
    return stations;
}

std::vector<std::string> parse_countries(const std::vector<nlohmann::json>& countries_jsons)
{
    std::vector<std::string> countries_names;
    countries_names.reserve(countries_jsons.size());
    for(const auto& json : countries_jsons)
    {
        countries_names.push_back(json["value"].get<std::string>());
    }
    return countries_names;
}

std::vector<std::string> parse_languages(const std::vector<nlohmann::json>& languages_jsons)
{
    std::vector<std::string> languages_names;
    languages_names.reserve(languages_jsons.size());
    for(const auto& json : languages_jsons)
    {
        languages_names.push_back(json["value"].get<std::string>());
    }
    return languages_names;
}

