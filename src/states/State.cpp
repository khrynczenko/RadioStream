#include "../../include/states/StatesManager.hpp"
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include "../../include/StreamManager.hpp"
#include "../../include/StationsManager.hpp"


State::Context::Context(nana::form& window, nana::menubar& menubar, StreamManager& stream_manager, StationsManager& stations_manager)
	: window(window)
	, menubar(menubar)
	, stream_manager(stream_manager)
	, stations_manager(stations_manager)
{

}

State::State(StatesManager& state_manager, Context& context)
	: context_(context)
	, manager_(state_manager)
{

}

void State::pop_error(const std::string& str) const
{
	str.c_str();
}

void State::switch_state(States::ID id) const
{
	manager_.switch_state(id);
}

