#ifndef STATIONSDATABASECONTROLLER_HPP
#define STATIONSDATABASECONTROLLER_HPP
#include "Controller.hpp"

class StationsDatabaseController : public Controller
{
public:
    StationsDatabaseController(StatesManager& manager, State::Context context);
    void process_event_command(const events::Event e, std::any data) override;
};

#endif