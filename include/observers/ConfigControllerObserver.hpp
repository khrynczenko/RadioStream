#ifndef CONFIGCONTROLLEROBSERVER_HPP
#define CONFIGCONTROLLEROBSERVER_HPP 

#include "Observer.hpp"
#include "../controllers/ConfigController.hpp"

class ConfigControllerObserver : public Observer
{
public:
    explicit ConfigControllerObserver(ConfigController& controller) noexcept;
    void on_notify(const std::any& data, radiostream::Event e) override;
private:
    ConfigController& controller_;
};

#endif
