#include "../../include/states/State.hpp"
#include "../../include/states/StatesManager.hpp"
#include "../../include/StreamManager.hpp"
#include "../../include/StationsManager.hpp"
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/menubar.hpp>

State::Context::Context(nana::form& window, nana::menubar& menubar, StreamManager& stream_manager, StationsManager& stations_manager , StatusBar& status)
	: window(window)
	, menubar(menubar)
	, stream_manager(stream_manager)
	, stations_manager(stations_manager)
    , status(status)
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

