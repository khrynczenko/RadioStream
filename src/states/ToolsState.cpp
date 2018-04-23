#include "../../include/states/ToolsState.hpp"
#include "../../include/Config.hpp"
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/form.hpp>

ToolsState::ToolsState(StatesManager& state_manager, Context& context)
    : State(state_manager, context)
    , container_(context.window_)
    , language_label_(context.window_)
	, language_choices_(context.window_)
    , found_stations_limit_(context.window_)
    , found_stations_values_(context.window_)
	, back_button_(context.window_)
	, apply_button_(context.window_)
{
	build_interface();
}

void ToolsState::change_visibility(bool visible)
{
	container_.field_display("content", visible);
	context_.menubar_.show();
}
void ToolsState::build_interface()
{
    language_label_.caption(context_.localizer_.get_localized_text("Language:"));
	language_choices_.push_back("English");
	language_choices_.push_back("Polski");

    found_stations_limit_.caption(context_.localizer_.get_localized_text("Search stations limit:"));
    found_stations_limit_.tooltip(context_.localizer_.get_localized_text("When You search for stations its possible that there will bee so many matching values that it will take quite long to process them."
        "This option limits this and can improve performance of searching."));
    found_stations_values_.range(1, 1000, 10);
	back_button_.caption(context_.localizer_.get_localized_text("Back"));
	back_button_.events().click([this]()
	{
		switch_state(States::ID::Main);
	});

	apply_button_.caption(context_.localizer_.get_localized_text("Apply"));
	apply_button_.events().click([this]()
	{
		const auto choosen_language_index = language_choices_.option();
		const std::string language = language_choices_.text(choosen_language_index);
		auto code = get_language_iso_identifier(language);
        notify(std::make_any<LanguageCode>(code), radiostream::Event::ConfigChangeLanguage);
		//TODO pop a message that for the langauge to change program must be restarted
	});

	container_.div(
		"<vert content margin=[5%,0,0,0]"
			"<settings_sections weight=20%"
                "<vert general"
                    "<language_pair arrange=[20%,20%] margin=1%>"
                    "<found_limit_pair arrange=[20%,20%] margin=1%>"
                ">"
			">"
			"<buttons_section weight=10% gap=80% margin=[80%,1%,10%,1%]>"
		">");
	container_.field("language_pair") << language_label_ << language_choices_;
    container_.field("found_limit_pair") << found_stations_limit_ << found_stations_values_;
	container_.field("buttons_section") << back_button_<< apply_button_;
	container_.collocate();
}

std::string ToolsState::get_language_iso_identifier(const std::string& language) const
{
	if (language == "Polski")
	{
		return "pl";
	}
	else if(language == "English")
	{
		return "en";
	}
    throw;
    //TODO Create according exception
}
