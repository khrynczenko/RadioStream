#include "../../include/observers/StationsDatabaseObserver.hpp"

StationsDatabaseObserver::StationsDatabaseObserver(StationsDatabaseController& controller)
    : controller_(controller)
{
}

void StationsDatabaseObserver::on_notify(const std::any& data, radiostream::Event e)
{
    controller_.process_event_command(e, data);
}
