#include "../../include/controllers/ConfigController.hpp"
#include "../../include/Config.hpp"

ConfigController::ConfigController(StatesManager& manager, State::Context context)
    : Controller(manager, context)
{
}

void ConfigController::process_event_command(const events::Event e, std::any data)
{
    switch(e)
    {
    case events::Event::ConfigChangeLanguage:
    {
        context_.config.change_language(std::any_cast<LanguageCode>(data));
    }
    }
}
