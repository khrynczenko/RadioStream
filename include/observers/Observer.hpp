#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "../states/StatesManager.hpp"
#include "Events.hpp"

class Observer
{
protected:
    using Context = State::Context;
public:
	virtual ~Observer() = default;
	virtual void on_notify(const nana::widget& caller, Context context,events::Event e) = 0;
};

#endif