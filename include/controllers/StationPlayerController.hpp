#ifndef STATIONPLAYERCONTROLLER_HPP
#define STATIONPLAYERCONTROLLER_HPP
#include "Controller.hpp"

class HTTPMultimediaPlaylistsDownloader;

class StationPlayerController : public Controller
{
public:
    StationPlayerController(StatesManager& manager, State::Context context, std::unique_ptr<HTTPMultimediaPlaylistsDownloader> downloader) noexcept;
    void process_event_command(const radiostream::Event e, std::any data) override;
private:
    std::unique_ptr<HTTPMultimediaPlaylistsDownloader> downloader_;
};
#endif
