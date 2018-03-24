#ifndef MAINSTATEOBSERVER_HPP
#define MAINSTATEOBSERVER_HPP
#include "Observer.hpp"
#include "../states/StatesManager.hpp"

class MainState;

class MainStateObserver : public Observer
{
public:
    MainStateObserver(MainState& state) noexcept;
    void on_notify(const std::any& data, radiostream::Event e) override;
private:
    MainState& state_;
};

#endif