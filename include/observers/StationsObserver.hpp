#ifndef STATIONSOBSERVER_HPP
#define STATIONSOBSERVER_HPP

#include "Observer.hpp"

class StationsObserver :
    public Observer
{
public:
    void on_notify(const std::any& any, Context context, events::Event e) override;
};

#endif