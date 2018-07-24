#include "../../include/states/StatesManager.hpp"
#include <stdexcept>

StatesManager::StatesManager(Context context)
	: context_(context)
{
}

void StatesManager::switch_state(States::ID id)
{
    if (states_.find(id) == states_.end())
    {
		throw std::runtime_error("State not registred.");
    }
	for (auto& state : states_)
	{
        state.second->change_visibility(state.first == id);
	}
}
