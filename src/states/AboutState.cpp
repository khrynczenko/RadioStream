#include "../../include/states/AboutState.hpp"
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/menubar.hpp>

AboutState::AboutState(StatesManager& state_manager, Context& context) 
    : State(state_manager, context)
    , container_(context.window_)
    , about_label_(context.window_)
    , back_button_(context.window_)
{
    build_interface();
}

void AboutState::change_visibility(bool visible) {
	container_.field_display("content", visible);
	context_.menubar_.show();
    container_.collocate();
}

void AboutState::build_interface() {
    about_label_.caption(context_.localizer_.get_localized_text("RadioStream version 0.1.1 by Krzysztof Hrynczenko.\n"
                                                                "For more information visit https://github.com/khrynczenko/RadioStream"));
                                                                //TODO: Get version from cmake file
                                                                //TODO: Finish and translate
	back_button_.caption(context_.localizer_.get_localized_text("Back"));
	back_button_.events().click([this]()
	{
		switch_state(States::ID::Main);
	});

	container_.div(
		"<vert content margin=[5%,0,0,0]"
			"<label_section weight=20%>"
			"<buttons_section weight=10% margin=[84%,90%,6%,1%]>"
		">");
	container_.field("label_section") << about_label_;
	container_.field("buttons_section") << back_button_;
	container_.collocate();
}