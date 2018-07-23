#ifndef STATUSBARCONTROLLEROBSERVER_HPP
#define STATUSBARCONTROLLEROBSERVER_HPP

#include "Observer.hpp"
class Controller;

class StatusBarControllerObserver : public Observer
{
public:
    explicit StatusBarControllerObserver(Controller& controller) noexcept;
    void on_notify(const std::any& data, radiostream::Event e) override;
private:
    Controller& controller_;
};

#endif