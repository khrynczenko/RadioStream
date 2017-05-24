#include "../include/StatesManager.hpp"



StatesManager::StatesManager(Context context)
	: context(context)
{
}

void StatesManager::switch_state(States::ID id)
{
	if (states.find(id) == states.end())
		throw std::exception("State not registred.");
	for (auto& state : states)
	{
		if (state.first == id)
			state.second->change_visibility(true);
		else
			state.second->change_visibility(false);
	}
}
