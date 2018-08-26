#include "../../include/controllers/StationPlayerController.hpp"
#include "../../include/StationPlayer.hpp"
#include "../../include/Constants.hpp"
#include "../../include/Utilities.hpp"
#include "../../include/multimedia_playlists/HTTPDownloader.hpp"
#include "../../include/multimedia_playlists/PLSReader.hpp"
#include "../../include/multimedia_playlists/MultimediaPlaylistReaderFactory.hpp"
#include "../../include/exceptions/ReaderCouldNotReadUrl.hpp"
#include <Poco/Net/NetException.h>
#include <thread>


StationPlayerController::StationPlayerController(StatesManager& manager,
    State::Context context,
    std::unique_ptr<HTTPDownloader> downloader) noexcept
    : Controller(manager, context)
    , downloader_(std::move(downloader))
{
}

void StationPlayerController::on_notify(const radiostream::Event e, const std::any &data)
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
            try
            {
                std::stringstream playlist_data{ downloader_->download(station.url_) };
                station.url_ = MultimediaPlaylistReaderFactory::make_reader(Poco::URI(station.url_))->get_station_url(playlist_data);
            }
            catch(const Poco::UnknownURISchemeException& e)
            {
                auto link_error_message = context_.localizer_.get_localized_text("Link is not valid");
                context_.status_.change_text(link_error_message);
                context_.status_.change_color(StatusBar::Color::ERRORED);
                break;
            }
            catch(ReaderCouldNotReadUrl& e)
            {
                auto link_error_message = context_.localizer_.get_localized_text("Link is not valid");
                context_.status_.change_text(link_error_message);
                context_.status_.change_color(StatusBar::Color::ERRORED);
                break;
            }
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
