#ifndef MAINSTATE_HPP
#define MAINSTATE_HPP

#include "State.hpp"
#include "../observers/Subject.hpp"
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/slider.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menu.hpp>
#include <thread>

class MainState :
    public State
{
public:
    MainState(StatesManager& manager, Context& context);
    void change_visibility(bool visible) override;
private:
    void build_interface();
    void init_contextual_menus();
    void init_listbox();
    void update_titles();
    void update_song_label();
    void update_station_label();
    void subscribe_to_station();
    void populate_listbox();
    void search_stations();
    void pop_song_title_menu();
    void pop_stations_listbox_menu();
    void set_new_stream();
    void delete_station();
    nana::place container_;
    nana::label current_song_label_;
    nana::label current_station_label_;
    nana::button play_button_;
    nana::button pause_button_;
    nana::button mute_button_;
    nana::textbox search_textbox_;
    nana::listbox stations_listbox_;
    nana::slider volume_slider_;
    nana::menu song_label_menu_;
    nana::menu listbox_item_menu_;
    nana::menu listbox_category_menu_;
    std::thread song_title_updater_;
    std::mutex song_title_mutex_;
    Subject subject_;
};

#endif
