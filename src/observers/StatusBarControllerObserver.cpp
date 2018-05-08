#include "../../include/observers/StatusBarControllerObserver.hpp"
#include "../../include/controllers/Controller.hpp"

StatusBarControllerObserver::StatusBarControllerObserver(Controller& controller) noexcept
    : controller_(controller)
{
}

void StatusBarControllerObserver::on_notify(const std::any& data, radiostream::Event e)
{
    controller_.process_event_command(e, data);
}
