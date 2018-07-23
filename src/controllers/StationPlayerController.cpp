#include "../../include/controllers/StationPlayerController.hpp"
#include "../../include/StationPlayer.hpp"
#include "../../include/Constants.hpp"
#include "../../include/Utilities.hpp"
#include "../../include/multimedia_playlists/HTTPMultimediaPlaylistsDownlader.hpp"
#include "../../include/multimedia_playlists/PLSReader.hpp"
#include "../../include/multimedia_playlists/MultimediaPlaylistReaderFactory.hpp"
#include <thread>


StationPlayerController::StationPlayerController(StatesManager& manager,
    State::Context context,
    std::unique_ptr<HTTPMultimediaPlaylistsDownloader> downloader) noexcept
    : Controller(manager, context)
    , downloader_(std::move(downloader))
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
        std::thread thread = std::thread([this]()
        {
            context_.station_player_.play();
        });
        thread.detach();
    }
    break;

    case radiostream::Event::VolumeChanged:
    {
        context_.station_player_.set_volume(volume_int_to_float(std::any_cast<unsigned>(data)));
    }
    break;
    
    case radiostream::Event::NewStationRequested:
    {
        auto station = std::any_cast<Station>(data);
        if (ends_with(station.url_, ".pls") || ends_with(station.url_, ".m3u"))
        {
            std::stringstream playlist_data{ downloader_->download(station.url_) };
            station.url_ = MultimediaPlaylistReaderFactory::make_reader(Poco::URI(station.url_))->get_station_url(playlist_data);
        }
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
