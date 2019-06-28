#include "../include/Application.hpp"
#include "../include/states/MainState.hpp"
#include "../include/states/SearchState.hpp"
#include "../include/states/ToolsState.hpp"
#include "../include/StatusBar.hpp"
#include "../include/Config.hpp"
#include "../include/Language.hpp"
#include "../include/exceptions/NotSupportedLanguageException.hpp"
#include "../include/Constants.hpp"
#include "../include/multimedia_playlists/PocoHTTPDownloader.hpp"
#include "../include/Utilities.hpp"
#include <nana/gui/msgbox.hpp>

Application::Application(const std::filesystem::path& config_directory_path,
                         const std::filesystem::path& data_directory_path,
                         const std::filesystem::path& lang_directory_path)
    : config_(config_directory_path / constants::CONFIG_FILE)
    , window_(nana::API::make_center(config_.options().window_width,
                                     config_.options().window_height),
                                     nana::appear::decorate<nana::appear::minimize,
                                                            nana::appear::sizable,
                                                            nana::appear::maximize,
                                                            nana::appear::taskbar>())
    , menubar_(window_)
    , stations_database_(data_directory_path / constants::STATIONS_DATABASE_FILE)
    , status_(window_)
    , localizer_(lang_directory_path)
    , requester_(config_.options().stations_search_limit)
    , context_(window_, menubar_, station_player_, stations_database_, status_, localizer_, config_, requester_)
    , states_manager_(context_)
    , general_container_(window_)
    , station_player_controller(std::make_shared<StationPlayerController>(states_manager_,
                                                                          context_,
                                                                          std::make_unique<PocoHTTPDownloader>()))
    , stations_database_controller_(std::make_shared<StationsDatabaseController>(states_manager_, context_))
    , config_controller_(std::make_shared<ConfigController>(states_manager_, context_))
    , radio_browser_requester_controller_(std::make_shared<RadioBrowserRequesterController>(states_manager_, context_))
    , status_bar_controller_(std::make_shared<StatusBarController>(states_manager_, context_, status_))
{
	set_language();
	init_menubar();
    init_status();
    register_states();
	set_observers();
    build_interface();
    auto search_state = states_manager_.get_state<SearchState>(States::ID::Search);
    search_state->initialize_countries_combox();
    search_state->initialize_language_combox();
	states_manager_.switch_state(States::ID::Main);
    set_window();
}

void Application::register_states()
{
	states_manager_.register_state<MainState>(States::ID::Main);
	states_manager_.register_state<SearchState>(States::ID::Search);
	states_manager_.register_state<ToolsState>(States::ID::Tools);
}

void Application::init_menubar()
{
	menubar_.push_back(localizer_.get_localized_text("File"));
    menubar_.push_back(localizer_.get_localized_text("Stations"));
	menubar_.push_back(localizer_.get_localized_text("Tools"));
	menubar_.push_back(localizer_.get_localized_text("Help"));

	menubar_.at(FILE).append(localizer_.get_localized_text("Open URL"), [this](nana::menu::item_proxy&)
	{
        std::thread thread([&]()
        {
            std::lock_guard<std::mutex> lock(mutex_);
            nana::inputbox::text url(localizer_.get_localized_text("URL"));
            nana::inputbox inbox(window_, localizer_.get_localized_text("Please write correct URL."), localizer_.get_localized_text("Open URL"));
            if (inbox.show(url))
            {
                notify(std::make_any<Station>("Unknown", url.value(), "", "", "", "", ""), radiostream::Event::NewStationRequested);
            }
        });
        thread.detach();
	});

    menubar_.at(FILE).append(localizer_.get_localized_text("Add station"), [this](nana::menu::item_proxy&)
    {   
        nana::inputbox::text station_name(localizer_.get_localized_text("Station's name"));
        nana::inputbox::text url(localizer_.get_localized_text("URL"));
        nana::inputbox::text country(localizer_.get_localized_text("Country"));
        nana::inputbox::text language(localizer_.get_localized_text("Language"));
        nana::inputbox::text codec(localizer_.get_localized_text("Codec"));
        nana::inputbox::text bitrate(localizer_.get_localized_text("Bitrate"));
        nana::inputbox::text tags(localizer_.get_localized_text("Tags"));
        nana::inputbox inbox(window_, localizer_.get_localized_text("Please write correct URL."), localizer_.get_localized_text("Add station"));
        if (inbox.show(station_name, url, country, language, codec, bitrate, tags))
        {
            notify(std::make_any<Station>(station_name.value(), url.value(), country.value(), language.value(),
                codec.value(), bitrate.value(), tags.value()), radiostream::Event::AddStationToDatabase);
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

	menubar_.at(HELP).append(localizer_.get_localized_text("About"), [this](nana::menu::item_proxy&)
	{
		// states_manager_.switch_state(States::ID::About);
        std::string message = context_.localizer_.get_localized_text(
            "RADIO_ABOUT"
        );
        auto message_with_version = replace_dollar_with_version_number(message);
        const std::string about = context_.localizer_.get_localized_text("About");
        nana::msgbox box{context_.window_, about};
        box << message_with_version;
        box.show();
	});

}

void Application::set_language()
{
	const auto language = LanguageCode(config_["language"].get<std::string>());
	localizer_.switch_language(language);
}

void Application::set_observers()
{
    auto main_state = states_manager_.get_state<MainState>(States::ID::Main);
    main_state->attach(station_player_controller);
    main_state->attach(stations_database_controller_);
    auto search_state = states_manager_.get_state<SearchState>(States::ID::Search);
    search_state->attach(station_player_controller);
    search_state->attach(stations_database_controller_);
    search_state->attach(radio_browser_requester_controller_);
    auto tools_state = states_manager_.get_state<ToolsState>(States::ID::Tools);
    tools_state->attach(config_controller_);
    this->attach(station_player_controller);
    this->attach(stations_database_controller_);
    station_player_.attach(main_state);
    station_player_.attach(status_bar_controller_);
    stations_database_.attach(main_state);
}

void Application::set_window_events()
{
    window_.events().resized([this](const nana::arg_resized& arg)
    {
        config_["height"] = arg.height;
        config_["width"] = arg.width;
    });
}

void Application::set_window()
{
	window_.caption("RadioStream");
    window_.show();
    set_window_events();
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
