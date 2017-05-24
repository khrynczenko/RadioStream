#ifndef STREAMOBSERVER_HPP
#define STREAMOBSERVER_HPP


#include "Observer.hpp"
#include <nana/gui/widgets/slider.hpp>

class StreamObserver :
	public Observer
{
public:
	StreamObserver() = default;
	void on_notify(const nana::widget& caller, Context context, events::Event e) override;
};

#endif