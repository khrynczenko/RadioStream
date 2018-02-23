#ifndef TOOLSSTATE_HPP
#define TOOLSSTATE_HPP

#include "State.hpp"
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/place.hpp>

class ToolsState : public State
{
public:
	ToolsState(StatesManager& state_manager, Context& context);
	void change_visibility(bool visible) override;
private:
	void build_interface();
private:
	std::string get_language_iso_identifier(const std::string& language) const;
	nana::place container_;
	nana::combox language_choices_;
	nana::button back_button_;
	nana::button apply_button_;
};

#endif
