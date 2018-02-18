#ifndef RADIOBROWSEREQUESTER_HPP
#define RADIOBROWSEREQUESTER_HPP

#include "RadioBrowserStation.hpp"
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/URI.h>
#include <nlohmann/json.hpp>
#include <vector>

class RadioBrowserRequester
{
public:
    enum class OrderBy
    {
        ClickCount,
        ClickTrend,
        Votes
    };
    std::vector<nlohmann::json> request_stations(std::string search_phrase, OrderBy order);
private:
    nlohmann::json send_arbitrary_request(Poco::URI request_uri,
        std::vector<std::pair<std::string, std::string>> request_paramters);
    std::string correct_json_response(std::string response) const;
    unsigned short int limit_ = 100;
    Poco::Net::HTTPClientSession session_{"www.radio-browser.info"};
};

std::vector<RadioBrowserStation> parse_stations_jsons(const std::vector<nlohmann::json>& stations_jsons);
#endif