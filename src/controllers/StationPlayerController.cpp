#include "../../include/controllers/StationPlayerController.hpp"
#include "../../include/StationPlayer.hpp"
#include "../../include/Constants.hpp"
#include "../../include/Utilities.hpp"
#include "../../include/multimedia_playlists/HTTPDownloader.hpp"
#include "../../include/multimedia_playlists/PLSReader.hpp"
#include "../../include/multimedia_playlists/MultimediaPlaylistReaderFactory.hpp"
#include "../../include/exceptions/ReaderCouldNotReadUrl.hpp"
#pragma warning(push, 0)
#include <Poco/Net/NetException.h>
#pragma warning(pop)
#include <thread>

using namespace std::string_literals;

StationPlayerController::StationPlayerController(
    StatesManager& manager, State::Context context,
    std::unique_ptr<HTTPDownloader> downloader) noexcept
    : Controller(manager, context), resolver_(std::move(downloader)) {}

void StationPlayerController::on_notify(const radiostream::Event e,
                                        const std::any& data) {
    using namespace constants;
    switch (e) {
        case radiostream::Event::PauseClicked: {
            context_.station_player_.pause();
        } break;

        case radiostream::Event::PlayClicked: {
            std::thread thread =
                std::thread([this]() { context_.station_player_.play(); });
            thread.detach();
        } break;

        case radiostream::Event::VolumeChanged: {
            context_.station_player_.set_volume(
                volume_int_to_float(std::any_cast<unsigned>(data)));
        } break;

        case radiostream::Event::NewStationRequested: {
            auto station = std::any_cast<Station>(data);
            const auto resolved =
                resolver_.resolve_uri(Poco::URI(station.url_));
            station.url_ = resolved.value_or(Poco::URI(""s)).toString();
            std::thread thread = std::thread([this, station]() {
                if (context_.station_player_.set_station(station))
                    context_.station_player_.play();
            });
            thread.detach();
        } break;

        case radiostream::Event::MuteClicked: {
            context_.station_player_.mute();
        } break;

        case radiostream::Event::MuteUnclicked: {
            context_.station_player_.unmute();
        } break;

        default:
            return;
    }
}
