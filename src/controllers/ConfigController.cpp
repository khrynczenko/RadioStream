#include "../../include/controllers/ConfigController.hpp"
#include "../../include/Config.hpp"

ConfigController::ConfigController(StatesManager& manager, State::Context context)
    : Controller(manager, context)
{
}

void ConfigController::process_event_command(const radiostream::Event e, std::any data)
{
    switch(e)
    {
    case radiostream::Event::ConfigChangeLanguage:
    {
        context_.config_.change_language(std::any_cast<LanguageCode>(data));
    }
    }
}
