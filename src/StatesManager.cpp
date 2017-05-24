#include "../include/StatesManager.hpp"



StatesManager::StatesManager(Context context)
	: context_(context)
{
}

void StatesManager::switch_state(States::ID id)
{
	if (states_.find(id) == states_.end())
		throw std::exception("State not registred.");
	for (auto& state : states_)
	{
		if (state.first == id)
			state.second->change_visibility(true);
		else
			state.second->change_visibility(false);
	}
}
