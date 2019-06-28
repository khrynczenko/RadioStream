#ifndef ABOUTSTATE_HPP
#define ABOUTSTATE_HPP

#include "State.hpp"
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>

class AboutState : public State 
{
public:
	AboutState(StatesManager& state_manager, Context& context);
	void change_visibility(bool visible) override;
private:
	void build_interface();
    nana::place container_;
    nana::label about_label_;
	nana::button back_button_;
};

#endif