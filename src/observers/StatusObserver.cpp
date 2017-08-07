#include "../../include/observers/StatusObserver.hpp"
#include "../../include/StatusBar.hpp"

void StatusObserver::on_notify(const std::any& any, Context context, events::Event e)
{
    switch (e)
    {

    case events::Event::NormalStatus:
    {
        auto& status = context.status;
        status.change_color(nana::colors::green);
        status.change_text("Ready");
    }
    break;

    case events::Event::LoadingStreamStatus:
    {
        auto& status = context.status;
        status.change_color(nana::colors::light_yellow);
        status.change_text("Loading station...");
    }
    break;

    case events::Event::SearchingStationsStatus:
    {
        auto& status = context.status;
        status.change_color(nana::colors::light_yellow);
        status.change_text("Searching stations...");
    }
    break;

    }
}
