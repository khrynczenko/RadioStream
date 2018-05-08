#include "../include/Application.hpp"
#include "../include/states/MainState.hpp"
#include "../include/states/SearchState.hpp"
#include "../include/states/ToolsState.hpp"
#include "../include/StatusBar.hpp"
#include "../include/Config.hpp"
#include "../include/Language.hpp"
#include "../include/exceptions/NotSupportedLanguageException.hpp"
#include "../include/Constants.hpp"
#include "../include/observers/StationPlayerControllerObserver.hpp"
#include "../include/observers/StationsDatabaseControllerObserver.hpp"
#include "../include/observers/ConfigControllerObserver.hpp"
#include "../include/observers/RadioBrowserRequesterControllerObserver.hpp"
#include "../include/observers/MainStateObserver.hpp"
#include "../include/observers/StatusBarControllerObserver.hpp"
#include <nana/gui/msgbox.hpp>

Application::Application()
    : window_(nana::API::make_center(800, 600), nana::appear::decorate<nana::appear::minimize, nana::appear::sizable, nana::appear::maximize, nana::appear::taskbar>())
    , menubar_(window_)
    , station_player_()
    , stations_database_(constants::STATIONS_DATABASE_FILE)
    , status_(window_)
    , localizer_()
    , config_(constants::CONFIG_FILE_PATH)
    , context_(window_, menubar_, station_player_, stations_database_, status_, localizer_, config_, requester_)
    , states_manager_(context_)
    , general_container_(window_)
    , station_player_controller(states_manager_, context_)
    , stations_database_controller_(states_manager_, context_)
    , config_controller_(states_manager_, context_)
    , radio_browser_requester_controller_(states_manager_, context_)
    , status_bar_controller_(states_manager_, context_, status_)
    , subject_()
{
	window_.caption("RadioStream");
	set_language();
	init_menubar();
    init_status();
    register_states();
	set_observers();
    build_interface();
    auto& search_state = states_manager_.get_state<SearchState>(States::ID::Search);
    search_state.initialize_countries_combox();
    search_state.initialize_language_combox();
	states_manager_.switch_state(States::ID::Main);
    window_.show();
}

void Application::register_states()
{
	states_manager_.register_state<MainState>(States::ID::Main);
	states_manager_.register_state<SearchState>(States::ID::Search);
	states_manager_.register_state<ToolsState>(States::ID::Tools);
}

void Application::init_menubar()
{
	menubar_.push_back(localizer_.get_localized_text("File:"));
    menubar_.push_back(localizer_.get_localized_text("Stations:"));
	menubar_.push_back(localizer_.get_localized_text("Tools:"));

	menubar_.at(FILE).append(localizer_.get_localized_text("Open URL"), [this](nana::menu::item_proxy&)
	{
        std::thread thread([&]()
        {
            std::lock_guard<std::mutex> lock(mutex_);
            nana::inputbox::text url(localizer_.get_localized_text("URL"));
            nana::inputbox inbox(window_, localizer_.get_localized_text("Please write correct URL."), localizer_.get_localized_text("Open URL"));
            if (inbox.show(url))
            {
                notify(std::make_any<Station>("Unknown", url.value(), false), radiostream::Event::NewStationRequested);
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
            notify(std::make_any<Station>(station_name.value(), url.value(), false), radiostream::Event::AddStationToDatabase);
        }
    });

    menubar_.at(RADIOBROWSER).append(localizer_.get_localized_text("Find stations"), [this](nana::menu::item_proxy&)
    {
        states_manager_.switch_state(States::ID::Search);
    });

	menubar_.at(TOOLS).append(localizer_.get_localized_text("Settings"), [this](nana::menu::item_proxy&)
	{
		states_manager_.switch_state(States::ID::Tools);
	});
}

void Application::set_language()
{
	const auto language = LanguageCode(config_["language"].get<std::string>());
	localizer_.switch_language(language);
}

void Application::set_observers()
{
    auto& main_state = states_manager_.get_state<MainState>(States::ID::Main);
    main_state.attach(std::make_unique<StationPlayerControllerObserver>(station_player_controller));
    main_state.attach(std::make_unique<StationsDatabaseControllerObserver>(stations_database_controller_));
    auto& search_state = states_manager_.get_state<SearchState>(States::ID::Search);
    search_state.attach(std::make_unique<StationPlayerControllerObserver>(station_player_controller));
    search_state.attach(std::make_unique<StationsDatabaseControllerObserver>(stations_database_controller_));
    search_state.attach(std::make_unique<RadioBrowserRequesterControllerObserver>(radio_browser_requester_controller_));
    auto& tools_state = states_manager_.get_state<ToolsState>(States::ID::Tools);
    tools_state.attach(std::make_unique<ConfigControllerObserver>(config_controller_));
    this->attach(std::make_unique<StationPlayerControllerObserver>(station_player_controller));
    this->attach(std::make_unique<StationsDatabaseControllerObserver>(stations_database_controller_));
    station_player_.attach(std::make_unique<MainStateObserver>(main_state));
    station_player_.attach(std::make_unique<StatusBarControllerObserver>(status_bar_controller_));
    stations_database_.attach(std::make_unique<MainStateObserver>(main_state));
}

void Application::build_interface()
{
    general_container_.div("<status_ weight=100% gap=1% margin=[97%,0%,0%,0%]>");
    general_container_.field("status_") << status_;
    general_container_.collocate();
}

void Application::init_status()
{
    status_.change_text(localizer_.get_localized_text("Ready"));
    status_.change_color(StatusBar::Color::FINISHED);
}
