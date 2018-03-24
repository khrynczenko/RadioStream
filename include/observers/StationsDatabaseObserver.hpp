#ifndef STATIONSDATABASEOBSERVER_HPP
#define STATIONSDATABASEOBSERVER_HPP
#include "Observer.hpp"
#include "../controllers/StationsDatabaseController.hpp"

class StationsDatabaseObserver : public Observer
{
public:
    StationsDatabaseObserver(StationsDatabaseController& controller) noexcept;
    void on_notify(const std::any& data, radiostream::Event e) override;
private:
    StationsDatabaseController& controller_;
};

#endif
