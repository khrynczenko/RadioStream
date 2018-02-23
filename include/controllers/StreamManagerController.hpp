#ifndef STREAMMANAGERCONTROLLER_HPP
#define STREAMMANAGERCONTROLLER_HPP
#include "Controller.hpp"

class StreamManagerController : public Controller
{
public:
    StreamManagerController(StatesManager& manager, State::Context context);
    void process_event_command(const events::Event e, std::any data) override;
};
#endif
