#ifndef STREAMOBSERVER_HPP
#define STREAMOBSERVER_HPP

#include "Observer.hpp"

class StreamObserver :
    public Observer
{
public:
    void on_notify(const std::any& any, Context context, events::Event e) override;
};

#endif
