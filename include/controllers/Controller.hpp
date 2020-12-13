#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../../include/states/State.hpp"
#include "../Observer.hpp"
#include <any>

namespace radiostream {
enum class Event;
}

class StatesManager;

class Controller : public Observer

{
   public:
    Controller(StatesManager& manager, State::Context context) noexcept;
    virtual void on_notify(const radiostream::Event e, const std::any& data) = 0;
    virtual ~Controller() = default;

   protected:
    StatesManager& manager_;
    State::Context context_;
};

#endif