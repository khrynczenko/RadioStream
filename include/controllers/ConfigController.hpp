#ifndef CONFIGCONTROLLER_HPP
#define CONFIGCONTROLLER_HPP
#include "Controller.hpp"

class ConfigController : public Controller {
   public:
    ConfigController(StatesManager& manager, State::Context context) noexcept;
    void on_notify(const radiostream::Event e, const std::any& data) override;
};

#endif