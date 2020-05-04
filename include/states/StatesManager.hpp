#ifndef STATESMANAGER_HPP
#define STATESMANAGER_HPP

#include "State.hpp"
#pragma warning (push, 0)
#include <nana/gui/widgets/form.hpp>
#pragma warning (pop)
#include <map>

/**
 * \brief Stores registred states, shows only one at time.
 * 
 */
class StatesManager
{
    using Context = State::Context;
public:
    explicit StatesManager(Context context);
	StatesManager() = delete;
	StatesManager(const StatesManager&) = delete;
	StatesManager& operator=(const StatesManager&) = delete;
	void switch_state(States::ID id);
	template<typename T>
	void register_state(States::ID id);
    template<typename T>
    std::shared_ptr<T> get_state(States::ID id);
private:
	Context context_;
	std::map<States::ID, std::shared_ptr<State>> states_;
};

/**
 * \brief Adds new State to the StatesManager dictionary.
 * \tparam T Type of State (should be a class derived from a State).
 * \param id States::ID that should be associated with given State.
 */
template <typename T>
void StatesManager::register_state(States::ID id)
{
	states_.insert(std::make_pair(id, std::make_shared<T>(*this, context_)));
}

template <typename T>
std::shared_ptr<T> StatesManager::get_state(States::ID id)
{
    return std::dynamic_pointer_cast<T>(states_.at(id));
}

#endif
