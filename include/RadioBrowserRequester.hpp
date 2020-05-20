#ifndef RADIOBROWSEREQUESTER_HPP
#define RADIOBROWSEREQUESTER_HPP

#include "Station.hpp"
#pragma warning(push, 0)
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/URI.h>
#include <nlohmann/json.hpp>
#pragma warning(pop)
#include <vector>

class RadioBrowserRequester {
   public:
    using Parameters = const std::vector<std::pair<std::string, std::string>>&;
    explicit RadioBrowserRequester(unsigned short int search_stations_limit);
    enum class OrderBy { ClickCount, ClickTrend, Votes };
    [[nodiscard]] std::vector<nlohmann::json> request_stations(
        std::string_view search_phrase, std::string_view country,
        std::string_view language, OrderBy order);
    [[nodiscard]] std::vector<nlohmann::json> request_countries();
    [[nodiscard]] std::vector<nlohmann::json> request_languages();

   private:
    [[nodiscard]] nlohmann::json send_arbitrary_request(
        const Poco::URI& request_uri, Parameters request_parameters);
    [[nodiscard]] std::string correct_json_response(std::string response) const;
    unsigned short int limit_ = 100;
    Poco::Net::HTTPClientSession session_{"www.radio-browser.info"};
};

[[nodiscard]] std::vector<Station> parse_stations_jsons(
    const std::vector<nlohmann::json>& stations_jsons);
[[nodiscard]] std::vector<std::string> parse_countries(
    const std::vector<nlohmann::json>& countries_jsons);
[[nodiscard]] std::vector<std::string> parse_languages(
    const std::vector<nlohmann::json>& languages_jsons);
#endif