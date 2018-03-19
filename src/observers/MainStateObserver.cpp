#include "../../include/observers/MainStateObserver.hpp"
#include "../../include/states/MainState.hpp"

MainStateObserver::MainStateObserver(MainState& state)
    : state_(state)
{
}

void MainStateObserver::on_notify(const std::any& data, radiostream::Event e)
{
    switch(e)
    {
    case radiostream::Event::StationBeingPlayedChanged:
        {
        auto station = std::any_cast<Station>(data);
        state_.station_being_played_changed(station);
        }
        break;
    case radiostream::Event::StationSongHasChanged:
        {
        state_.song_has_changed(std::any_cast<std::string>(data));
        }
    }
}
