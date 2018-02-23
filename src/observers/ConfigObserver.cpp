#include "../../include/observers/ConfigObserver.hpp"

ConfigObserver::ConfigObserver(ConfigController& controller)
    : controller_(controller)
{
}

void ConfigObserver::on_notify(const std::any& data, events::Event e)
{
    controller_.process_event_command(e, data);
}
