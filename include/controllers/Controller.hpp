#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../../include/states/State.hpp"
#include <any>

namespace radiostream {
    enum class Event;
}

class StatesManager;

class Controller
   
{
public:
    Controller(StatesManager& manager, State::Context context) noexcept;
    virtual void process_event_command(const radiostream::Event e, std::any data) = 0;
    virtual ~Controller() = default;
protected:
    StatesManager& manager_;
    State::Context context_;
};

#endif