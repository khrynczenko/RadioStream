#include "../../include/observers/Subject.hpp"

void Subject::attach(std::unique_ptr<Observer> observer)
{
	observers_.emplace_back(std::move(observer));
}

void Subject::notify(const std::any& data, events::Event e)
{
    for (auto& observer : observers_)
    {
		observer->on_notify(data, e);
    }
}
