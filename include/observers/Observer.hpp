#ifndef OBSERVER_HPP
#define OBSERVER_HPP
#include "../StatesManager.hpp"
#include "Events.hpp"
#include "../Utilities.hpp"

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void on_notify(const nana::widget& caller, Context context,events::Event e) = 0;
};

#endif