#include "../../include/states/ToolsState.hpp"
#include "../../include/Config.hpp"
#include "../../include/Constants.hpp"
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/msgbox.hpp>

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
    LanguageCode chosen_language(context_.config_["language"].get<std::string>());
    language_choices_.push_back(constants::LANGUAGES_CODES_AND_NATIVE_NAMES.at(chosen_language));
    language_choices_.option(0);
    for (const auto[key, value] : constants::LANGUAGES_CODES_AND_NATIVE_NAMES)
    {
        if (key.as_string() != chosen_language.as_string()) language_choices_.push_back(value);
    }
    found_stations_limit_.caption(context_.localizer_.get_localized_text("Search stations limit:"));
    found_stations_limit_.tooltip(context_.localizer_.get_localized_text("When You search for stations its possible that there will bee so many matching values that it will take quite long to process them."
        "This option limits this and can improve performance of searching."));
    const auto limit = context_.config_["stations_search_limit"].get<unsigned int>();
    found_stations_values_.range(1, 1000, 10);
    found_stations_values_.value(std::to_string(limit));
	back_button_.caption(context_.localizer_.get_localized_text("Back"));
	back_button_.events().click([this]()
	{
		switch_state(States::ID::Main);
	});

	apply_button_.caption(context_.localizer_.get_localized_text("Apply"));
	apply_button_.events().click([this]()
	{
        notify(std::make_any<ConfigOptions>(gather_options()), radiostream::Event::ConfigApplyNewChanges);
        pop_restart_program_message_box();
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

void ToolsState::pop_restart_program_message_box() const
{
    nana::msgbox restart_program_message{ context_.window_, "Restart program" };
    restart_program_message << context_.localizer_.get_localized_text("In order to apply the changes program needs to be restarted.");
    restart_program_message.show();
}

ConfigOptions ToolsState::gather_options() const
{
    ConfigOptions options;
    const auto language_native_name = language_choices_.text(language_choices_.option());
    options.language = string_to_language_code(language_native_name);
    options.stations_search_limit = found_stations_values_.to_int();
    return options;
}

LanguageCode ToolsState::string_to_language_code(const std::string& language_native_name) const
{
    for (const auto&[key, value] : constants::LANGUAGES_CODES_AND_NATIVE_NAMES)
    {
        if (value == language_native_name)
        {
            return key;
        }
    }
    throw;
}

