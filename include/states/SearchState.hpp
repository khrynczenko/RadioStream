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
    void initialize_language_combox();
    void initialize_countries_combox();
    void change_visibility(bool visible) override;
    void init_listbox();
    void build_interface();
    void insert_stations_to_listbox(const std::vector<Station>& stations);
    void insert_possible_languages(const std::vector<std::string>& languages);
    void insert_possible_countires(const std::vector<std::string>& countries);
private:
    void search_for_stations();
    void set_new_station();
    void pop_stations_listbox_menu();
    void add_selected_station_to_database();
    void sticky_select(const nana::arg_mouse & mouse);
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
