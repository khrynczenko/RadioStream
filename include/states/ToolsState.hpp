#ifndef TOOLSSTATE_HPP
#define TOOLSSTATE_HPP

#include "State.hpp"
#include "../observers/Subject.hpp"
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/combox.hpp>

class ToolsState : public State
{
public:
	ToolsState(StatesManager& state_manager, Context& context);
	void change_visibility(bool visible) override;
private:
	void add_observers();
	void build_interface();
private:
	std::string get_language_iso_identifier(const std::string& language) const;
	Subject subject_;
	nana::place container_;
	nana::combox language_choices_;
	nana::button back_button_;
	nana::button apply_button_;
};

#endif
