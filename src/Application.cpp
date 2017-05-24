#include "../include/Application.hpp"
#include "../include/MainState.hpp"
#include <nana/gui/msgbox.hpp>
#include <iostream>

Application::Application()
	: window(nana::API::make_center(600, 500), nana::appear::decorate<nana::appear::minimize, nana::appear::sizable, nana::appear::maximize, nana::appear::taskbar>())
	, states_manager(State::Context{ window, menubar, stream_manager, stations_manager})
	, menubar(window)
	, stream_manager()
	, stations_manager()
{
	window.caption("Radio Client");
	init_menubar();
	register_states();
	states_manager.switch_state(States::ID::Main);
	window.show();
}

void Application::register_states()
{
	states_manager.register_state<MainState>(States::ID::Main);
}

void Application::init_menubar()
{
	enum
	{
		FILE,
		SETTINGS
	};
	menubar.push_back("File: ");
	menubar.push_back("Settings: ");
	menubar.at(FILE).append("Open URL", [this](nana::menu::item_proxy& ip)
	{
		nana::inputbox::text url("<bold blue>URL</>");	//The format text is also available, the second parameter can be given for default value
		nana::inputbox inbox(window, "Please write correct URL.\n\n\n", "Open URL");
		if (inbox.show_modal(url))
		{
			stream_manager.set_new_stream(url.value());
			stream_manager.play();
		}
	});
	menubar.hide();
}
