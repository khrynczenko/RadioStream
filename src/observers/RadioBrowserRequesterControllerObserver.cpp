#include "../../include/observers/RadioBrowserRequesterControllerObserver.hpp"

RadioBrowserRequesterControllerObserver::RadioBrowserRequesterControllerObserver(
    RadioBrowserRequesterController& controller) noexcept
    : controller_(controller)
{
}

void RadioBrowserRequesterControllerObserver::on_notify(const std::any& data, radiostream::Event e)
{
    controller_.process_event_command(e, data);
}
