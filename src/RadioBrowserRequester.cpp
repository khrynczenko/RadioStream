#include "../../include/RadioBrowserRequester.hpp"
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <nlohmann/detail/conversions/from_json.hpp>

std::vector<nlohmann::json> RadioBrowserRequester::request_stations(std::string search_phrase, OrderBy order)
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
    request_parameters.emplace_back("name", search_phrase);
    request_parameters.emplace_back("limit", std::to_string(limit_));
    request_parameters.emplace_back("order", order_value);
    request_parameters.emplace_back("reverse", "true");
    auto response = send_arbitrary_request(advanced_search_uri, request_parameters);
    return response["response"].get<std::vector<nlohmann::json>>();
}



std::string RadioBrowserRequester::correct_json_response(std::string response) const
{
    //radio-browser API returns not valid JSON object which makes in unparsable by nlohmann library,
    //this little change corrects it.
    response.push_back('}');
    return "{ \"response\" : " + response;
}

nlohmann::json RadioBrowserRequester::send_arbitrary_request(Poco::URI request_uri,
    std::vector<std::pair<std::string, std::string>> request_paramters)
{
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, request_uri.toString());
    std::string request_body;
    for(const auto& [parameter_name, parameter_value] : request_paramters)
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

std::vector<RadioBrowserStation> parse_stations_jsons(const std::vector<nlohmann::json>& stations_jsons)
{
    std::vector<RadioBrowserStation> stations;
    stations.reserve(stations_jsons.size());
    for(const auto& station_json : stations_jsons)
    {
        stations.emplace_back(station_json["name"].get<std::string>(),
            station_json["url"].get<std::string>(),
            station_json["country"].get<std::string>(),
            station_json["language"].get<std::string>());
    }
    return stations;
}

