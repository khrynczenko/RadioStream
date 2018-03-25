#include "../../include/observers/StationsDatabaseControllerObserver.hpp"

StationsDatabaseControllerObserver::StationsDatabaseControllerObserver(StationsDatabaseController& controller) noexcept
    : controller_(controller) 
{
}

void StationsDatabaseControllerObserver::on_notify(const std::any& data, radiostream::Event e)
{
    controller_.process_event_command(e, data);
}
