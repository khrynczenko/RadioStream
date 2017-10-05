#ifndef TEXTLOCALIZEROBSERVER_HPP
#define TEXTLOCALIZEROBSERVER_HPP
#include "Observer.hpp"

class TextLocalizerObserver 
	: public Observer
{
public:
	void on_notify(const std::any& any, Context context, events::Event e) override;
};

#endif
