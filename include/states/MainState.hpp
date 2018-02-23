#ifndef MAINSTATE_HPP
#define MAINSTATE_HPP

#include "State.hpp"
#include "../observers/Subject.hpp"
#include "../Station.hpp"
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
    void set_station_name(const std::string& name);
    void refresh_listbox();
private:
    /**
     * \brief normally when the same row is selected second time it gets unselected, this function prevents that.
     */
    void select_row_without_unselect_feature(const nana::arg_listbox& selected_row);
    bool check_if_row_was_right_clicked(const nana::arg_mouse& arg) const;
    void run_concurrent_song_name_updater();
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
    Station get_station_from_listbox(unsigned long long int category_index, unsigned long long int row_index) const;
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
    std::mutex mutex_;
};

#endif
