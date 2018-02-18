#ifndef STATE_HPP
#define STATE_HPP

#include "StateIdentifiers.hpp"
#include "../StreamManager.hpp"
#include "../StationsDatabase.hpp"
#include "../StatusBar.hpp"
#include "../TextLocalizer.hpp"


class Config;

namespace nana {
	class menubar;
	class form;
}

class StatesManager;

class State
{
public:
	virtual ~State() = default;

	/**
	 * \brief Context represents a structure containing references to items use throughout all states
	 */
	struct Context
	{
		Context(nana::form& window,
                nana::menubar& menubar,
                StreamManager& stream_manager,
                StationsDatabase& stations_database ,
                StatusBar& status,
				TextLocalizer& localizer,
				Config& config
		);
		nana::form& window;
		nana::menubar& menubar;
		StreamManager& stream_manager;
		StationsDatabase& stations_database;
        StatusBar& status;
		TextLocalizer& localizer;
		Config& config;
	};
	State(StatesManager& state_manager, Context& context);
	virtual void change_visibility(bool visible) = 0;
protected:
	void switch_state(States::ID id) const;
	Context& context_;
private:
	StatesManager& manager_;
};

#endif