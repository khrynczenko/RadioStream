#include "../../include/observers/StationPlayerControllerObserver.hpp"

StationPlayerControllerObserver::StationPlayerControllerObserver(StationPlayerController& controller) noexcept
    : controller_(controller)
{
}

void StationPlayerControllerObserver::on_notify(const std::any& data, radiostream::Event e)
{
    controller_.process_event_command(e, data);
}
