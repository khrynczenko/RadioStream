#ifndef CONFIGOBSERVER_HPP
#define CONFIGOBSERVER_HPP 

#include "Observer.hpp"
#include "../controllers/ConfigController.hpp"

class ConfigObserver : public Observer
{
public:
    explicit ConfigObserver(ConfigController& controller) noexcept;
    void on_notify(const std::any& data, radiostream::Event e) override;
private:
    ConfigController& controller_;
};

#endif
