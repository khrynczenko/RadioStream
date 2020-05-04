#ifndef STATUSBARCONTROLLER_HPP
#define STATUSBARCONTROLLER_HPP

#include "Controller.hpp"

class StatusBarController : public Controller {
   public:
    StatusBarController(StatesManager& manager, State::Context context,
                        StatusBar& statusbar) noexcept;
    void on_notify(const radiostream::Event e, const std::any& data) override;

   private:
    StatusBar& statusbar_;
};

#endif  // !STATUSBARCONTROLLER_HPP
