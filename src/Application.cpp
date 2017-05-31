#include "../include/Application.hpp"
#include <nana/gui/msgbox.hpp>
#include "../include/states/MainState.hpp"

Application::Application()
	: window_(nana::API::make_center(600, 500), nana::appear::decorate<nana::appear::minimize, nana::appear::sizable, nana::appear::maximize, nana::appear::taskbar>())
	, states_manager_(State::Context{ window_, menubar_, stream_manager_, stations_manager_})
	, menubar_(window_)
	, stream_manager_()
	, stations_manager_()
{
	window_.caption("Radio Client");
	init_menubar();
	register_states();
	states_manager_.switch_state(States::ID::Main);
	window_.show();
}

void Application::register_states()
{
	states_manager_.register_state<MainState>(States::ID::Main);
}

void Application::init_menubar()
{
	enum
	{
		FILE,
		SETTINGS
	};
	menubar_.push_back("File: ");
	menubar_.push_back("Settings: ");
	menubar_.at(FILE).append("Open URL", [this](nana::menu::item_proxy& ip)
	{
		nana::inputbox::text url("<bold blue>URL</>");	//The format text is also available, the second parameter can be given for default value
		nana::inputbox inbox(window_, "Please write correct URL.\n\n\n", "Open URL");
		if (inbox.show_modal(url))
		{
			stream_manager_.set_new_stream(url.value());
			stream_manager_.play();
		}
	});
	menubar_.hide();
}
