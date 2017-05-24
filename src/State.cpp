#include "../include/State.hpp"
#include "../include/StatesManager.hpp"

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
	
}

void State::switch_state(States::ID id) const
{
	manager_.switch_state(id);
}

