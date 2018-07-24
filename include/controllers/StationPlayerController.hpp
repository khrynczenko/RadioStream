#ifndef STATIONPLAYERCONTROLLER_HPP
#define STATIONPLAYERCONTROLLER_HPP
#include "Controller.hpp"

class HTTPMultimediaPlaylistsDownloader;

class StationPlayerController : public Controller
{
public:
    StationPlayerController(StatesManager& manager, State::Context context, std::unique_ptr<HTTPMultimediaPlaylistsDownloader> downloader) noexcept;
    void on_notify(const radiostream::Event e, const std::any &data) override;
private:
    std::unique_ptr<HTTPMultimediaPlaylistsDownloader> downloader_;
};
#endif
