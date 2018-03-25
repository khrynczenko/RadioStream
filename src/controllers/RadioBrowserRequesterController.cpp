#include "../../include/controllers/RadioBrowserRequesterController.hpp"
#include "../../include/RadioBrowserRequester.hpp"
#include "../../include/states/StatesManager.hpp"
#include "../../include/states/SearchState.hpp"

RadioBrowserRequesterController::RadioBrowserRequesterController(StatesManager& manager,
    State::Context context) noexcept
    : Controller(manager, context)
{
}

void RadioBrowserRequesterController::process_event_command(const radiostream::Event e, std::any data)
{
    switch(e)
    {
    case radiostream::Event::SearchStationsRequested:
    {
        auto[search_phrase, country, language, order] = std::any_cast<std::tuple<std::string, std::string, std::string, RadioBrowserRequester::OrderBy>>(data);
        const auto requested_stations = context_.requester_.request_stations(search_phrase, country, language, order);
        const auto parsed_stations = parse_stations_jsons(requested_stations);
        manager_.get_state<SearchState>(States::ID::Search).insert_stations_to_listbox(parsed_stations);
    }
    break;
    case radiostream::Event::SearchLanguagesRequested:
    {
    const auto requested_languages = context_.requester_.request_languages();
    const auto parsed_languages = parse_languages(requested_languages);
    manager_.get_state<SearchState>(States::ID::Search).insert_possible_languages(parsed_languages);
    }
    break;
    case radiostream::Event::SearchCountriesRequested:
    {
    const auto requested_countries = context_.requester_.request_countries();
    const auto parsed_countries = parse_languages(requested_countries);
    manager_.get_state<SearchState>(States::ID::Search).insert_possible_countires(parsed_countries);
    }
    break;


    }
}
