#ifndef STATESMANAGER_HPP
#define STATESMANAGER_HPP

#include "State.hpp"
#include <nana/gui/widgets/form.hpp>
#include <map>

/**
 * \brief Stores registred states, shows only one at time.
 * 
 */
class StatesManager
{
    using Context = State::Context;
public:
	StatesManager(Context context);
	StatesManager() = delete;
	StatesManager(const StatesManager&) = delete;
	StatesManager& operator=(const StatesManager&) = delete;
	void switch_state(States::ID id);
	template<typename T>
	void register_state(States::ID id);
    template<typename T>
    T& get_state(States::ID id);
private:
	Context context_;
	std::map<States::ID, std::unique_ptr<State>> states_;
};

/**
 * \brief Adds new State to the StatesManager map.
 * \tparam T Type of State (should be a class derived from a State).
 * \param id States::ID that should be associated with given State.
 */
template <typename T>
void StatesManager::register_state(States::ID id)
{
	states_.insert(std::make_pair(id, std::make_unique<T>(*this, context_)));
}

template <typename T>
T& StatesManager::get_state(States::ID id)
{
    return *(dynamic_cast<T*>(states_.at(id).get()));
}

#endif
