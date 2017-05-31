#ifndef MAINSTATE_HPP
#define MAINSTATE_HPP

#include "State.hpp"
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/slider.hpp>
#include <nana/gui/widgets/label.hpp>
#include "../observers/Subject.hpp"

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
	nana::place container_;
	nana::label current_song_label_;
	nana::label current_station_label_;
	nana::button play_button_;
	nana::button pause_button_;
	nana::textbox search_textbox_;
	nana::listbox stations_listbox_;
	nana::slider volume_slider_;
	std::thread song_title_updater_;
	std::mutex song_title_mutex_;
	Subject subject_;
};

#endif