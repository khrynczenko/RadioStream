#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include "Observer.hpp"
#include <vector>
#include <memory>


class Subject
{
public:
	void attach(std::unique_ptr<Observer> observer);
	void notify(const std::any& data, events::Event e);
private:
	std::vector<std::unique_ptr<Observer>> observers_;
};

#endif
