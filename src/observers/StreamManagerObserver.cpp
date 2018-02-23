#include "../../include/observers/StreamManagerObserver.hpp"

StreamManagerObserver::StreamManagerObserver(StreamManagerController& controller)
    : controller_(controller)
{
}

void StreamManagerObserver::on_notify(const std::any& data, events::Event e)
{
    controller_.process_event_command(e, data);
}
