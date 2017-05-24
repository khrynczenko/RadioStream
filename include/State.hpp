#ifndef STATE_HPP
#define STATE_HPP

#include <nana\gui\widgets\form.hpp>
#include "StateIdentifiers.hpp"
#include "StreamManager.hpp"
#include "StationsManager.hpp"


namespace nana {
	class menubar;
}

class StatesManager;

class State
{
public:
	virtual ~State() = default;
	//Context represents a structure containing references to items use throughout all states
	struct Context
	{
		Context(nana::form& window, nana::menubar& menubar, StreamManager& stream_manager, StationsManager& stations_manager);
		nana::form& window;
		nana::menubar& menubar;
		StreamManager& stream_manager;
		StationsManager& stations_manager;
	};
	State(StatesManager& state_manager, Context& context);
	virtual void change_visibility(bool visibile) = 0;
protected:
	void pop_error(const std::string& str) const;
	void switch_state(States::ID id) const;
	Context& context;
private:
	StatesManager& manager;
};

#endif