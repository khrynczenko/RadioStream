#ifndef MAINSTATE_HPP
#define MAINSTATE_HPP

#include "State.hpp"
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/slider.hpp>
#include <nana/gui/widgets/label.hpp>
#include <chrono>
#include "observers/Subject.hpp"

class MainState :
	public State
{
	friend class MainStateObserver;
public:
	MainState(StatesManager& manager, Context& context);
	void change_visibility(bool visible) override;
private:
	void build_interface();
	void init_listbox();
	void populate_listbox();
	void update_titles();
	nana::place container;
	nana::label current_song_label;
	nana::label current_station_label;
	nana::button play_button;
	nana::button pause_button;
	nana::textbox search_textbox;
	nana::listbox stations_listbox;
	nana::slider volume_slider;
	std::thread song_title_updater;
	std::mutex song_title_mutex;
	Subject subject;
};

#endif