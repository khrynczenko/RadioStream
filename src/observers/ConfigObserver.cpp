#include "../../include/observers/ConfigObserver.hpp"

ConfigObserver::ConfigObserver(ConfigController& controller) noexcept
    : controller_(controller)
{
}

void ConfigObserver::on_notify(const std::any& data, radiostream::Event e)
{
    controller_.process_event_command(e, data);
}
