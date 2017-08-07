#pragma once
#include "Observer.hpp"
class StatusObserver :
    public Observer
{
public:
    void on_notify(const std::any& any, Context context, events::Event e) override;
};

