#ifndef TOOLSSTATE_HPP
#define TOOLSSTATE_HPP

#include "State.hpp"
#include "../Config.hpp"
#pragma warning(push, 0)
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/spinbox.hpp>
#pragma warning(pop)

class ToolsState : public State {
   public:
    ToolsState(StatesManager& state_manager, Context& context);
    void change_visibility(bool visible) override;

   private:
    void build_interface();
    void pop_restart_program_message_box() const;

   private:
    [[nodiscard]] ConfigOptions gather_options() const;
    [[nodiscard]] LanguageCode string_to_language_code(
        std::string_view language_native_name) const;
    nana::place container_;
    nana::label language_label_;
    nana::combox language_choices_;
    nana::label found_stations_limit_;
    nana::spinbox found_stations_values_;
    nana::button back_button_;
    nana::button apply_button_;
};

#endif
