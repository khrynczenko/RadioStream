#ifndef STATIONPLAYERCONTROLLEROBSERVER_HPP
#define STATIONPLAYERCONTROLLEROBSERVER_HPP
#include "Observer.hpp"
#include "../controllers/StationPlayerController.hpp"

class StationPlayerControllerObserver : public Observer
{
public:
    explicit StationPlayerControllerObserver(StationPlayerController& controller) noexcept;
    void on_notify(const std::any& data, radiostream::Event e) override;
private:
    StationPlayerController& controller_;
    
};

#endif
