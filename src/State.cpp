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
	: context(context)
	, manager(state_manager)
{

}

void State::pop_error(const std::string& str) const
{
	//context.popup = std::make_unique<ErrorPopup>(context.window, str);
}

void State::switch_state(States::ID id) const
{
	manager.switch_state(id);
}

