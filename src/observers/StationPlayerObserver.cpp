#include "../../include/observers/StationPlayerObserver.hpp"

StationPlayerObserver::StationPlayerObserver(StationPlayerController& controller)
    : controller_(controller)
{
}

void StationPlayerObserver::on_notify(const std::any& data, radiostream::Event e)
{
    controller_.process_event_command(e, data);
}
