#ifndef STATIONPLAYERCONTROLLER_HPP
#define STATIONPLAYERCONTROLLER_HPP
#include "Controller.hpp"
#include "../StreamURIResolver.hpp"
#include <Poco/URI.h>

class HTTPDownloader;

class StationPlayerController : public Controller
{
public:
    StationPlayerController(StatesManager& manager, State::Context context, std::unique_ptr<HTTPDownloader> downloader) noexcept;
    void on_notify(const radiostream::Event e, const std::any &data) override;
private:
    StreamURIResolver resolver_;
};

#endif
