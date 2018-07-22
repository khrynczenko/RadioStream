#include "../../include/observers/Subject.hpp"

void Subject::attach(std::shared_ptr<Observer> observer)
{
	observers_.emplace_back(observer);
}

void Subject::notify(const std::any& data, radiostream::Event e)
{
    for (auto& observer : observers_)
    {
		observer->on_notify(e, data);
    }
}
