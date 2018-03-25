#include "../../include/observers/ConfigControllerObserver.hpp"

ConfigControllerObserver::ConfigControllerObserver(ConfigController& controller) noexcept
    : controller_(controller)
{
}

void ConfigControllerObserver::on_notify(const std::any& data, radiostream::Event e)
{
    controller_.process_event_command(e, data);
}
