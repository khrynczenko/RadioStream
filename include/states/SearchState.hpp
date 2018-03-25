#ifndef RADIOBROWSERSTATE_HPP
#define RADIOBROWSERSTATE_HPP

#include "State.hpp"
#include "../RadioBrowserRequester.hpp"
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/menu.hpp>
#include <nana/gui/widgets/combox.hpp>

namespace nana {
    class menu;
}

class SearchState : public State
{
public:
    SearchState(StatesManager& state_manager, Context& context);
    void change_visibility(bool visible) override;
    void init_listbox();
    void build_interface();
private:
    void set_new_station();
    void pop_stations_listbox_menu();
    RadioBrowserRequester requester_;
    nana::place container_;
    nana::textbox search_textbox_;
    nana::label sort_by_label_;
    nana::combox sorting_combox_;
    nana::combox country_combox_;
    nana::combox language_combox_;
    nana::button search_submit_button_;
    nana::listbox found_stations_listbox_;
    nana::button back_button_;
    nana::menu listbox_right_click_menu_;
};

#endif
