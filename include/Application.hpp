#ifndef APP_HPP
#define APP_HPP

#include "states/StatesManager.hpp"
#include "StreamManager.hpp"
#include "StationsManager.hpp"
#include "observers/Subject.hpp"
#include "StatusBar.hpp"
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/menubar.hpp>

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
    StatusBar status_;
    State::Context context_;
    StatesManager states_manager_;
    nana::place general_container_;
    Subject subject_;
};


#endif
