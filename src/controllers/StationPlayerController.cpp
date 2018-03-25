#include "../../include/controllers/StationPlayerController.hpp"
#include "../../include/StationPlayer.hpp"
#include "../../include/Constants.hpp"
#include "../../include/Utilities.hpp"


StationPlayerController::StationPlayerController(StatesManager& manager, State::Context context)
    : Controller(manager, context)
{
}

void StationPlayerController::process_event_command(const radiostream::Event e, std::any data)
{
    using namespace constants;
    switch (e)
    {
    case radiostream::Event::PauseClicked:
    {
        context_.status_.change_text(context_.localizer_.get_localized_text("Stream paused"));
        context_.station_player_.pause();
        context_.status_.change_color(StatusBar::Color::FINISHED);
    }
    break;

    case radiostream::Event::PlayClicked:
    {
        context_.status_.change_text(context_.localizer_.get_localized_text("Stream playing"));
        context_.station_player_.play();
        context_.status_.change_color(StatusBar::Color::FINISHED);
    }
    break;

    case radiostream::Event::VolumeChanged:
    {
        context_.station_player_.set_volume(volume_int_to_float(std::any_cast<unsigned>(data)));
    }
    break;
    
    case radiostream::Event::NewStationRequested:
    {
        const auto station = std::any_cast<Station>(data);
        context_.status_.change_text(context_.localizer_.get_localized_text("Loading stream..."));
        context_.status_.change_color(StatusBar::Color::PROCESSING);
        context_.station_player_.set_station(station);
        context_.station_player_.play();
        context_.status_.change_text(context_.localizer_.get_localized_text("Stream playing"));
        context_.status_.change_color(StatusBar::Color::FINISHED);
    }
    break;

    case radiostream::Event::MuteClicked:
    {
        context_.station_player_.set_volume(0.f);
        context_.status_.change_text(context_.localizer_.get_localized_text("Stream muted"));
    }
    break;
    }
}
