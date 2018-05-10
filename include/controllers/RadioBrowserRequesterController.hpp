#ifndef RADIOBROWSERREQUESTERCONTROLLER_HPP
#define RADIOBROWSERREQUESTERCONTROLLER_HPP 

#include "Controller.hpp"
#include "../multimedia_playlists/HTTPMultimediaPlaylistsDownlader.hpp"

class HTTPMultimediaPlaylistsDownloader;

class RadioBrowserRequesterController : public Controller
{
public:
    explicit RadioBrowserRequesterController(StatesManager& manager, State::Context context) noexcept;
    void process_event_command(const radiostream::Event e, std::any data) override;
};


#endif