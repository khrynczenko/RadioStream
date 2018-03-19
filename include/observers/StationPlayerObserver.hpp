#ifndef STATIONPLAYEROBSERVER_HPP
#define STATIONPLAYEROBSERVER_HPP
#include "Observer.hpp"
#include "../controllers/StationPlayerController.hpp"

class StationPlayerObserver : public Observer
{
public:
    StationPlayerObserver(StationPlayerController& controller);
    void on_notify(const std::any& data, radiostream::Event e) override;
private:
    StationPlayerController& controller_;
    
};

#endif
