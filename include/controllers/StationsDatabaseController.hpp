#ifndef STATIONSDATABASECONTROLLER_HPP
#define STATIONSDATABASECONTROLLER_HPP
#include "Controller.hpp"

class StationsDatabaseController : public Controller
{
public:
    StationsDatabaseController(StatesManager& manager, State::Context context) noexcept;
    void process_event_command(const radiostream::Event e, std::any data) override;
};

#endif