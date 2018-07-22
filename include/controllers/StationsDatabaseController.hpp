#ifndef STATIONSDATABASECONTROLLER_HPP
#define STATIONSDATABASECONTROLLER_HPP
#include "Controller.hpp"

class StationsDatabaseController : public Controller
{
public:
    StationsDatabaseController(StatesManager& manager, State::Context context) noexcept;
    void on_notify(const radiostream::Event e, const std::any &data) override;
};

#endif