#ifndef CONFIGCONTROLLER_HPP
#define CONFIGCONTROLLER_HPP
#include "Controller.hpp"

class ConfigController : public Controller
{
public:
    ConfigController(StatesManager& manager, State::Context context);
    void process_event_command(const events::Event e, std::any data) override;
};

#endif