#include "../../include/states/State.hpp"
#include "../../include/states/StatesManager.hpp"
#include "../../include/StationPlayer.hpp"
#include "../../include/StationsDatabase.hpp"
#include "../../include/Config.hpp"
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/menubar.hpp>

State::Context::Context(nana::form& window,
		nana::menubar& menubar,
		StationPlayer& station_player,
		StationsDatabase& stations_database,
		StatusBar& status,
		TextLocalizer& localizer,
		Config& config) noexcept
	: window(window)
	, menubar(menubar)
	, station_player(station_player)
	, stations_database(stations_database)
    , status(status)
	, localizer(localizer)
	, config(config)
{

}

State::State(StatesManager& state_manager, Context& context)
	: context_(context)
	, manager_(state_manager)
{

}

void State::switch_state(States::ID id) const
{
	manager_.switch_state(id);
}

