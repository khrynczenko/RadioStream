#ifndef TOOLSSTATE_HPP
#define TOOLSSTATE_HPP

#include "State.hpp"
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/spinbox.hpp>

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
    nana::label language_label_;
	nana::combox language_choices_;
    nana::label found_stations_limit_;
    nana::spinbox found_stations_values_;
	nana::button back_button_;
	nana::button apply_button_;
};

#endif
