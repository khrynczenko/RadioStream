#include <nana/gui/widgets/menubar.hpp>
#include "../../include/states/MainState.hpp"
#include "../../include/observers/StreamObserver.hpp"
#include "../../include/observers/MainStateObserver.hpp"
#include "../../include/Constants.hpp"

MainState::MainState(StatesManager& manager, Context& context)
	: State(manager, context)
	, container_(context.window)
	, current_song_label_(context.window, "no song is playing")
	, current_station_label_(context.window, "no station is playing")
	, play_button_(context.window)
	, pause_button_(context.window)
	, search_textbox_(context.window)
	, stations_listbox_(context.window)
	, volume_slider_(context.window)
{
	subject_.attach(std::make_unique<StreamObserver>());
	subject_.attach(std::make_unique<MainStateObserver>(*this));
	build_interface();
	init_listbox();
	song_title_updater_ = std::thread(&MainState::update_titles, this);
	song_title_updater_.detach();
}

void MainState::change_visibility(bool visible)
{
	container_.field_display("content", visible);
	context_.menubar.show();
}

void MainState::build_interface()
{
	play_button_.caption("Play");
	pause_button_.caption("Pause");
	play_button_.events().click([this]()
	{
		subject_.notify(play_button_, context_, events::Event::STREAM_PLAY);
	});
	pause_button_.events().click([this]()
	{
		subject_.notify(play_button_, context_, events::Event::STREAM_PAUSE);
	});
	volume_slider_.scheme().color_vernier = constants::volume_slider_vernier_color;
	volume_slider_.maximum(100);
	volume_slider_.value(volume_float_to_int(context_.stream_manager.get_volume()));
	volume_slider_.vernier([](unsigned maximum, unsigned cursor_value)
	{
		return std::string(std::to_string(cursor_value) + "/" + std::to_string(maximum));
	});
	volume_slider_.events().value_changed([this](const nana::arg_slider& value)
	{
		subject_.notify(volume_slider_, context_, events::Event::VOLUME_CHANGED);
	});
	search_textbox_.line_wrapped(true).multi_lines(false).tip_string("Search...");
	search_textbox_.events().text_changed([this]()
	{
		subject_.notify(search_textbox_, context_, events::Event::SEARCH_STATIONS);
	});
	container_.div(
		"<content vertical margin=[5%,0,0,0]" 
		"<first_line weight=12% arrange=[10%,10%] gap=1% margin=1%>"
		"<between_line weight=10% arrange=[49%,48%] gap=1% margin=1% >"
		"<second_line weight=8% arrange=[25%,72%] gap=1% margin=1%>"
		"<listbox margin=1%>"
		">");
	container_.field("first_line") << play_button_ << pause_button_;
	container_.field("between_line") << current_station_label_ << current_song_label_;
	container_.field("second_line") << search_textbox_ << volume_slider_;
	container_.field("listbox") << stations_listbox_;
	container_.collocate();
}

void MainState::init_listbox()
{
	stations_listbox_.scheme().max_fit_content = 0;
	stations_listbox_.scheme().min_column_width = 1000;

	stations_listbox_.append_header("Station's name");
	stations_listbox_.enable_single(true, false);
	subject_.notify(stations_listbox_, context_, events::Event::POPULATE_LISTBOX);
	stations_listbox_.column_at(0).width(1000);
	stations_listbox_.events().dbl_click([this]()
	{
		subject_.notify( stations_listbox_, context_, events::Event::STREAM_NEW);
		subject_.notify( stations_listbox_, context_, events::Event::UPDATE_STATION_LABEL);
		subject_.notify(stations_listbox_, context_, events::Event::UPDATE_SONG_LABEL);
	});
}

void MainState::populate_listbox()
{
	stations_listbox_.auto_draw(false);
	for (const auto& station : context_.stations_manager.get_default_stations())
	{
		stations_listbox_.at(0).append({ station.name_ });
	}
	stations_listbox_.auto_draw(true);
}

void MainState::update_titles()
{
	using namespace std::chrono_literals;
	current_song_label_.caption(context_.stream_manager.get_song_title());
	while(true)
	{
		std::this_thread::sleep_for(10s);
		std::lock_guard<std::mutex>{song_title_mutex_};
		subject_.notify(stations_listbox_, context_, events::Event::UPDATE_SONG_LABEL);
	}
	
}
