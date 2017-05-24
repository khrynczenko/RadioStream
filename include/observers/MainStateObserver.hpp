#ifndef UIOBSERVER_HPP
#define UIOBSERVER_HPP

#include "Observer.hpp"

class MainState;

class MainStateObserver
	: public Observer
{
public:
	MainStateObserver(MainState& ui);
	void on_notify(const nana::widget& caller, Context context, events::Event e) override;
private:
	MainState& ui_;
};

#endif