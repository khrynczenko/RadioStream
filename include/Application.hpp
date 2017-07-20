#ifndef APP_HPP
#define APP_HPP

#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/msgbox.hpp>
#include "states/StatesManager.hpp"
#include "StreamManager.hpp"
#include "StationsManager.hpp"
#include "states/MainState.hpp"

/**
 * \class Application
 * \brief Glues each compomnent of a system together. Creates window, sets initial States, initializes menubar etc.
 */
class Application
{
public:
	Application();
private:
    /**
	 * \brief Gets called in constructor, register states that are gonna be used througout the application
	 */
	void register_states();
	void init_menubar();
	nana::form window_;
	nana::menubar menubar_;
	StreamManager stream_manager_;
	StationsManager stations_manager_;
    StatesManager states_manager_;
};


#endif
