#include "../include/Application.hpp"
#include "../include/states/MainState.hpp"
#include "../include/states/ToolsState.hpp"
#include "../include/observers/StatusObserver.hpp"
#include "../include/StatusBar.hpp"
#include <nana/gui/msgbox.hpp>
#include "../include/Config.hpp"
#include <iostream>


Application::Application()
	: window_(nana::API::make_center(600, 500), nana::appear::decorate<nana::appear::minimize, nana::appear::sizable, nana::appear::maximize, nana::appear::taskbar>())
	, menubar_(window_)
    , stream_manager_()
    , stations_manager_()
    , status_(window_)
	, localizer_()
	, config_(constants::CONFIG_FILE_PATH)
    , context_(window_, menubar_, stream_manager_, stations_manager_, status_, localizer_, config_)
    , states_manager_(context_)
    , general_container_(window_)
    , subject_()
{
	window_.caption("RadioStream");
	set_language();
	set_observers();
	init_menubar();
    register_states();
	states_manager_.switch_state(States::ID::Main);
    subject_.notify(Observer::placeholder, context_, events::Event::NormalStatus);
    general_container_.div("<status_ weight=100% gap=1% margin=[97%,0%,0%,0%]>");
    general_container_.field("status_") << status_;
    general_container_.collocate();
    window_.show();
}

void Application::register_states()
{
	states_manager_.register_state<MainState>(States::ID::Main);
	states_manager_.register_state<ToolsState>(States::ID::Tools);
}

void Application::init_menubar()
{
	enum
	{
		FILE,
		TOOLS
	};

	menubar_.push_back(localizer_.get_localized_text("File:"));
	menubar_.push_back(localizer_.get_localized_text("Tools:"));

	menubar_.at(FILE).append(localizer_.get_localized_text("Open URL"), [this](nana::menu::item_proxy&)
	{
        std::thread thread([&]()
        {
		nana::inputbox::text url(localizer_.get_localized_text("URL"));
		nana::inputbox inbox(window_, localizer_.get_localized_text("Please write correct URL."), localizer_.get_localized_text("Open URL"));
		if (inbox.show(url))
		{
                std::lock_guard<std::mutex> lock(mutex_);
                subject_.notify(Observer::placeholder, context_, events::Event::LoadingStreamStatus);
                stream_manager_.set_stream(url.value());
                stream_manager_.play();
                states_manager_.getState<MainState>(States::ID::Main).set_station_name(localizer_.get_localized_text("Undefined station"));
                subject_.notify(Observer::placeholder, context_, events::Event::StreamPlayingStatus);
            }
        });
        thread.detach();
	});

    menubar_.at(FILE).append(localizer_.get_localized_text("Add station"), [this](nana::menu::item_proxy&)
    {   
        nana::inputbox::text station_name(localizer_.get_localized_text("Station name:"));
        nana::inputbox::text url(localizer_.get_localized_text("URL:"));
        nana::inputbox inbox(window_, localizer_.get_localized_text("Please write correct URL."), localizer_.get_localized_text("Add station"));
        if (inbox.show(station_name, url))
        {
            stations_manager_.add_station(Station{ station_name.value(), url.value(), false, true });
        }
    });

	menubar_.at(TOOLS).append(localizer_.get_localized_text("Settings"), [this](nana::menu::item_proxy&)
	{
		states_manager_.switch_state(States::ID::Tools);
	});
}

void Application::set_language()
{
	const auto language = get_language(config_["language"].get<std::string>());
	localizer_.switch_language(language);
}

void Application::set_observers()
{
	subject_.attach(std::make_unique<StatusObserver>());
}

Language Application::get_language(const std::string& iso_identifier) const
{
	if (iso_identifier == "en")
	{
		return Language::EN;
	}
	else if (iso_identifier == "pl")
	{
		return Language::PL;
	}
	else
	{
		throw;
		//TODO create according expcetion
	}
}
