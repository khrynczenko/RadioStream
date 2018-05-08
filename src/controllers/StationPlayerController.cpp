#include "../../include/controllers/StationPlayerController.hpp"
#include "../../include/StationPlayer.hpp"
#include "../../include/Constants.hpp"
#include "../../include/Utilities.hpp"


StationPlayerController::StationPlayerController(StatesManager& manager, State::Context context) noexcept
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
        context_.station_player_.pause();
    }
    break;

    case radiostream::Event::PlayClicked:
    {
        context_.station_player_.play();
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
        std::thread thread = std::thread([this, station](){
            if(context_.station_player_.set_station(station))
                context_.station_player_.play();
        });
        thread.detach();
    }
    break;

    case radiostream::Event::MuteClicked:
    {
        context_.station_player_.mute();
    }
    break;

    case radiostream::Event::MuteUnclicked:
    {
        context_.station_player_.unmute();
    }
    break;
    }
}
