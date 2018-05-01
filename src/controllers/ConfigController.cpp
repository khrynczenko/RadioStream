#include "../../include/controllers/ConfigController.hpp"
#include "../../include/Config.hpp"

ConfigController::ConfigController(StatesManager& manager, State::Context context) noexcept
    : Controller(manager, context)
{
}

void ConfigController::process_event_command(const radiostream::Event e, std::any data)
{
    switch(e)
    {
    case radiostream::Event::ConfigApplyNewChanges:
    {
        auto options = std::any_cast<ConfigOptions>(data);
        context_.config_.change_language(options.language);
        context_.config_.change_stations_search_limit(options.stations_search_limit);
    }
    }
}
