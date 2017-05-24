#ifndef APP_HPP
#define APP_HPP
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include "StatesManager.hpp"
#include "StreamManager.hpp"
#include "StationsManager.hpp"

class Application
{
public:
	Application();
private:
	void register_states();
	void init_menubar();
	nana::form window;
	StatesManager states_manager;
	nana::menubar menubar;
	StreamManager stream_manager;
	StationsManager stations_manager;
};


#endif
