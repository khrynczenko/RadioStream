#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../../include/states/State.hpp"
#include <any>

namespace events {
    enum class Event;
}

class StatesManager;

class Controller
   
{
public:
    Controller(StatesManager& manager, State::Context context);
    virtual void process_event_command(const events::Event e, std::any data) = 0;
    virtual ~Controller() = default;
protected:
    StatesManager& manager_;
    State::Context context_;
};

#endif