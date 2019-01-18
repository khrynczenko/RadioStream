#ifndef APP_HPP
#define APP_HPP

#include "states/StatesManager.hpp"
#include "StationPlayer.hpp"
#include "StationsDatabase.hpp"
#include "Subject.hpp"
#include "StatusBar.hpp"
#include "TextLocalizer.hpp"
#include "Config.hpp"
#include "RadioBrowserRequester.hpp"
#include "controllers/StationPlayerController.hpp"
#include "controllers/StationsDatabaseController.hpp"
#include "controllers/ConfigController.hpp"
#include "controllers/RadioBrowserRequesterController.hpp"
#include "controllers/StatusBarController.hpp"
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <mutex>
#include <filesystem>

class LanguageCode;

/**
 * \class Application
 * \brief Glues each compomnent of a system together. Creates window, sets initial States, initializes menubar etc.
 */
class Application : public Subject
{
public:
	Application(const std::filesystem::path& config_directory_path,
			    const std::filesystem::path& data_directory_path,
			    const std::filesystem::path& lang_directory_path);
private:
    enum
    {
        FILE,
        RADIOBROWSER,
        TOOLS
    };
    /**
	 * \brief Gets called in constructor, registers states that are gonna be used throughout the application.
	 */
	void register_states();
	void init_menubar();
	void set_language();
	void set_observers();
    void set_window_events();
    void set_window();
    void build_interface();
    void init_status();
	Config config_;
	nana::form window_;
	nana::menubar menubar_;
    StationPlayer station_player_;
    StationsDatabase stations_database_;
    StatusBar status_;
	TextLocalizer localizer_;
    RadioBrowserRequester requester_;
    State::Context context_;
    StatesManager states_manager_;
    nana::place general_container_;
    std::shared_ptr<StationPlayerController> station_player_controller;
    std::shared_ptr<StationsDatabaseController> stations_database_controller_;
    std::shared_ptr<ConfigController> config_controller_;
    std::shared_ptr<RadioBrowserRequesterController> radio_browser_requester_controller_;
    std::shared_ptr<StatusBarController> status_bar_controller_;
    Subject subject_;
    std::mutex mutex_;
};

#endif
