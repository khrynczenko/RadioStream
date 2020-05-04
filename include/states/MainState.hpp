#ifndef MAINSTATE_HPP
#define MAINSTATE_HPP

#include "State.hpp"
#include "../Station.hpp"
#include "../widgets/StationListbox.hpp"
#pragma warning (push, 0)
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/slider.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menu.hpp>
#pragma warning (pop)
#include <thread>

class MainState :
    public State,
    public Observer
{
public:
    MainState(StatesManager& manager, Context& context);
    void change_visibility(bool visible) override;
    void refresh_listbox();
    void station_being_played_changed(const Station& changed_station);
    void song_has_changed(std::string_view song_title);
    void on_notify(radiostream::Event e, const std::any& data) override;
private:
    /**
     * \brief normally when the same row is selected second time it gets unselected, this function prevents that.
     */
    void build_interface();
    void init_contextual_menus();
    void set_listbox_events();
    void search_stations();
    void pop_song_title_menu();
    void pop_stations_listbox_menu();
    void copy_station_name_to_clipboard();
    void copy_station_url_to_clipboard();
    void delete_station();
    void on_new_station_request();
    nana::place container_;
    nana::label current_song_label_;
    nana::label current_station_label_;
    nana::button play_button_;
    nana::button pause_button_;
    nana::button mute_button_;
    nana::textbox search_textbox_;
    StationListbox stations_listbox_;
    nana::slider volume_slider_;
    nana::menu song_label_menu_;
    nana::menu listbox_item_menu_;
    nana::menu listbox_category_menu_;
    std::thread song_title_updater_;
    std::mutex song_title_mutex_;
    std::mutex mutex_;
};

#endif
