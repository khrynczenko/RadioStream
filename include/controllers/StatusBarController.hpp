#ifndef STATUSBARCONTROLLER_HPP
#define STATUSBARCONTROLLER_HPP

#include "Controller.hpp"

class StatusBarController : public Controller
{
public:
    StatusBarController(StatesManager& manager, State::Context context, StatusBar& statusbar) noexcept;
    void process_event_command(const radiostream::Event e, std::any data) override;
private:
    StatusBar& statusbar_;
};

#endif // !STATUSBARCONTROLLER_HPP
