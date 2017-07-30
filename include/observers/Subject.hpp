#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include "Observer.hpp"
#include <vector>


class Subject
{
    using Context = State::Context;
public:
	void attach(std::unique_ptr<Observer> observer);
	void notify(const std::any& caller, Context context, events::Event e);
private:
	std::vector<std::unique_ptr<Observer>> observers_;
};

#endif
