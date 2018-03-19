#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "Events.hpp"
#include <any>



class Observer
{
public:
	virtual ~Observer() = default;
	virtual void on_notify(const std::any& data, radiostream::Event e) = 0;
    static const std::any placeholder;
};

#endif