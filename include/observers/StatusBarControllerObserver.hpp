#ifndef STATUSBARCONTROLLEROBSERVER_HPP
#define STATUSBARCONTROLLEROBSERVER_HPP

#include "Observer.hpp"
class Controller;

class StatusBarControllerObserver : public Observer
{
public:
    StatusBarControllerObserver(Controller& controller) noexcept;
    virtual void on_notify(const std::any& data, radiostream::Event e) override;
private:
    Controller& controller_;
};

#endif