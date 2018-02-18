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
            status.change_text(context.localizer.get_localized_text("Ready"));
        }
        break;

    case events::Event::LoadingStreamStatus:
        {
            auto& status = context.status;
            status.change_color(nana::colors::orange);
            status.change_text(context.localizer.get_localized_text("Loading station..."));
        }
        break;

    case events::Event::SearchingStationsStatus:
        {
            auto& status = context.status;
            status.change_color(nana::colors::orange);
            status.change_text(context.localizer.get_localized_text("Searching stations..."));
        }
        break;

    case events::Event::StreamPlayingStatus:
        {
            auto& status = context.status;
            status.change_color(nana::colors::green);
            status.change_text(context.localizer.get_localized_text("Radio playing"));
        }
        break;

    case events::Event::StreamPausedStatus:
        {
            auto& status = context.status;
            status.change_color(nana::colors::yellow);
            status.change_text(context.localizer.get_localized_text("Radio paused"));
        }
        break;
    default: ;
    }
}
