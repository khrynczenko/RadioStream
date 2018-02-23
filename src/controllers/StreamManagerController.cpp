#include "../../include/controllers/StreamManagerController.hpp"
#include "../../include/Constants.hpp"
#include "../../include/Utilities.hpp"

StreamManagerController::StreamManagerController(StatesManager& manager, State::Context context)
    : Controller(manager, context)
{
}

void StreamManagerController::process_event_command(const events::Event e, std::any data)
{
    using namespace constants;
    switch (e)
    {
    case events::Event::StreamPause:
    {
        context_.status.change_text(context_.localizer.get_localized_text("Stream paused"));
        context_.stream_manager.pause();
        context_.status.change_color(StatusBar::Color::FINISHED);
    }
    break;

    case events::Event::StreamPlay:
    {
        context_.status.change_text(context_.localizer.get_localized_text("Stream playing"));
        context_.stream_manager.play();
        context_.status.change_color(StatusBar::Color::FINISHED);
    }
    break;

    case events::Event::StreamVolumeChanged:
    {
        context_.stream_manager.set_current_volume(volume_int_to_float(std::any_cast<unsigned>(data)));
    }
    break;

    case events::Event::StreamSetNewByName:
    {
        context_.status.change_text(context_.localizer.get_localized_text("Loading stream..."));
        context_.status.change_color(StatusBar::Color::PROCESSING);
        const auto station_name = std::any_cast<std::string>(data);
        const auto station_ip = context_.stations_database.get_station_ip(station_name);
        context_.stream_manager.set_stream(station_ip);
        context_.stream_manager.play();
        context_.status.change_text(context_.localizer.get_localized_text("Stream playing"));
        context_.status.change_color(StatusBar::Color::FINISHED);
    }
    break;

    case events::Event::StreamSetNewByIP:
    {
        context_.status.change_text(context_.localizer.get_localized_text("Loading stream..."));
        context_.status.change_color(StatusBar::Color::PROCESSING);
        const auto station_ip = std::any_cast<std::string>(data);
        context_.stream_manager.set_stream(station_ip);
        context_.stream_manager.play();
        context_.status.change_text(context_.localizer.get_localized_text("Stream playing"));
        context_.status.change_color(StatusBar::Color::FINISHED);
    }
    break;

    case events::Event::StreamMute:
    {
        context_.stream_manager.set_current_volume(0.f);
        context_.status.change_text(context_.localizer.get_localized_text("Stream muted"));
    }
    break;
    }
}
