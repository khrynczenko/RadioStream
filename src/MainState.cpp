#include "../include/MainState.hpp"
#include <nana/gui/widgets/menubar.hpp>
#include "../include/Utilities.hpp"
#include "../include/Constants.hpp"
#include "../include/observers/Observer.hpp"
#include "../include/observers/StreamObserver.hpp"
#include "../include/observers/MainStateObserver.hpp"

MainState::MainState(StatesManager& manager, Context& context)
	: State(manager, context)
	, container(context.window)
	, current_song_label(context.window, "no song is playing")
	, current_station_label(context.window, "no station is playing")
	, play_button(context.window)
	, pause_button(context.window)
	, search_textbox(context.window)
	, stations_listbox(context.window)
	, volume_slider(context.window)
{
	subject.attach(std::make_unique<StreamObserver>());
	subject.attach(std::make_unique<MainStateObserver>(*this));
	build_interface();
	init_listbox();
	song_title_updater = std::thread(&MainState::update_titles, this);
	song_title_updater.detach();

}

void MainState::change_visibility(bool visible)
{
	container.field_display("content", visible);
	context.menubar.show();
}

void MainState::build_interface()
{
	play_button.caption("Play");
	pause_button.caption("Pause");
	play_button.events().click([this]()
	{
		subject.notify(play_button, context, events::Event::STREAM_PLAY);
	});
	pause_button.events().click([this]()
	{
		subject.notify(play_button, context, events::Event::STREAM_PAUSE);
	});
	volume_slider.scheme().color_vernier = constants::volume_slider_vernier_color;
	volume_slider.maximum(100);
	volume_slider.value(volume_float_to_int(context.stream_manager.get_volume()));
	volume_slider.vernier([](unsigned maximum, unsigned cursor_value)
	{
		return std::string(std::to_string(cursor_value) + "/" + std::to_string(maximum));
	});
	volume_slider.events().value_changed([this](const nana::arg_slider& value)
	{
		subject.notify(volume_slider, context, events::Event::VOLUME_CHANGED);
	});
	search_textbox.line_wrapped(true).multi_lines(false).tip_string("Search...");
	search_textbox.events().text_changed([this]()
	{
		subject.notify(search_textbox, context, events::Event::SEARCH_STATIONS);
	});
	container.div(
		"<content vertical margin=[5%,0,0,0]" 
		"<first_line weight=12% arrange=[10%,10%] gap=1% margin=1%>"
		"<between_line weight=10% arrange=[49%,48%] gap=1% margin=1% >"
		"<second_line weight=8% arrange=[25%,72%] gap=1% margin=1%>"
		"<listbox margin=1%>"
		">");
	container.field("first_line") << play_button << pause_button;
	container.field("between_line") << current_station_label << current_song_label;
	container.field("second_line") << search_textbox << volume_slider;
	container.field("listbox") << stations_listbox;
	container.collocate();
}

void MainState::init_listbox()
{
	stations_listbox.scheme().max_fit_content = 0;
	stations_listbox.scheme().min_column_width = 1000;

	stations_listbox.append_header("Station's name");
	stations_listbox.enable_single(true, false);
	subject.notify(stations_listbox, context, events::Event::POPULATE_LISTBOX);
	stations_listbox.column_at(0).width(1000);
	stations_listbox.events().dbl_click([this]()
	{
		subject.notify( stations_listbox, context, events::Event::STREAM_NEW);
		subject.notify( stations_listbox, context, events::Event::UPDATE_STATION_LABEL);
		subject.notify(stations_listbox, context, events::Event::UPDATE_SONG_LABEL);
	});
}

void MainState::populate_listbox()
{
	stations_listbox.auto_draw(false);
	for (const auto& station : context.stations_manager.get_default_stations())
	{
		stations_listbox.at(0).append({ station.name });
	}
	stations_listbox.auto_draw(true);
}

void MainState::update_titles()
{
	using namespace std::chrono_literals;
	current_song_label.caption(context.stream_manager.get_song_title());
	while(true)
	{
		std::this_thread::sleep_for(10s);
		std::lock_guard<std::mutex>{song_title_mutex};
		subject.notify(stations_listbox, context, events::Event::UPDATE_SONG_LABEL);
	}
	
}
