#include "../../include/observers/Subject.hpp"

void Subject::attach(std::unique_ptr<Observer> observer)
{
	observers_.emplace_back(std::move(observer));
}

void Subject::notify(const nana::widget& caller, Context context, events::Event e)
{
	for (auto& observer : observers_)
		observer->on_notify(caller, context, e);
}
