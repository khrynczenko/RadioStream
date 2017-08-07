#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "../states/StatesManager.hpp"
#include "Events.hpp"
#include <any>



class Observer
{
protected:
    using Context = State::Context;
public:
	virtual ~Observer() = default;
	virtual void on_notify(const std::any& any, Context context, events::Event e) = 0;
    static const std::any placeholder;
};

#endif