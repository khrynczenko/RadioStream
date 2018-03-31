#ifndef STATIONPLAYERCONTROLLER_HPP
#define STATIONPLAYERCONTROLLER_HPP
#include "Controller.hpp"

class StationPlayerController : public Controller
{
public:
    StationPlayerController(StatesManager& manager, State::Context context) noexcept;
    void process_event_command(const radiostream::Event e, std::any data) override;
};
#endif
