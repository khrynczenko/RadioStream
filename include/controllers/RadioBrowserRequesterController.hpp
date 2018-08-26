#ifndef RADIOBROWSERREQUESTERCONTROLLER_HPP
#define RADIOBROWSERREQUESTERCONTROLLER_HPP 

#include "Controller.hpp"
#include "../multimedia_playlists/HTTPDownloader.hpp"

class HTTPDownloader;

class RadioBrowserRequesterController : public Controller
{
public:
    explicit RadioBrowserRequesterController(StatesManager& manager, State::Context context) noexcept;
    void on_notify(const radiostream::Event e, const std::any &data) override;
};


#endif