#ifndef STATESMANAGER_HPP
#define STATESMANAGER_HPP

#include "State.hpp"
#include <nana/gui/widgets/form.hpp>
#include <map>


using Context = State::Context;

class StatesManager
{
public:
	StatesManager(Context context);
	StatesManager() = delete;
	StatesManager(const StatesManager&) = delete;
	StatesManager& operator=(const StatesManager&) = delete;
	void switch_state(States::ID id);
	template<typename T>
	void register_state(States::ID id);
private:
	Context context_;
	std::map<States::ID, std::unique_ptr<State>> states_;
};

template <typename T>
void StatesManager::register_state(States::ID id)
{
	states_.insert(std::make_pair(id, std::make_unique<T>(*this, context_)));
}

#endif
