#include <nana/gui/widgets/menubar.hpp>
#include "../../include/states/MainState.hpp"
#include "../../include/observers/StreamObserver.hpp"
#include "../../include/observers/MainStateObserver.hpp"
#include "../../include/Constants.hpp"
#include "../../include/observers/StationsObserver.hpp"

using namespace constants;

MainState::MainState(StatesManager& manager, Context& context)
	: State(manager, context)
	, container_(context.window)
	, current_song_label_(context.window, "no song is playing")
	, current_station_label_(context.window, "no station is playing")
	, play_button_(context.window)
	, pause_button_(context.window)
	, mute_button_(context.window)
	, search_textbox_(context.window)
	, stations_listbox_(context.window)
	, volume_slider_(context.window)
    , song_label_menu_()
    , listbox_item_menu_()
{
	subject_.attach(std::make_unique<StreamObserver>(volume_slider_, mute_button_));
	subject_.attach(std::make_unique<MainStateObserver>(*this));
    subject_.attach(std::make_unique<StationsObserver>());
	build_interface();
    init_contextual_menus();
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
    current_song_label_.events().mouse_up([this](const nana::arg_mouse& arg)
    {
        if (!arg.is_left_button())
            subject_.notify(stations_listbox_, context_, events::Event::SongLabelContextualMenu);
    });
	play_button_.caption("Play");
    play_button_.events().click([this]()
    {
        subject_.notify(play_button_, context_, events::Event::StreamPlay);
    });
	pause_button_.caption("Pause");
	pause_button_.events().click([this]()
	{
		subject_.notify(pause_button_, context_, events::Event::StreamPause);
	});
	mute_button_.caption("Mute");
    mute_button_.enable_pushed(true);
    mute_button_.events().mouse_up([this]()
    {
        subject_.notify(mute_button_, context_, events::Event::StreamMute);
    });
	volume_slider_.scheme().color_vernier = VERNIER_COLOR;
	volume_slider_.maximum(100);
	volume_slider_.value(volume_float_to_int(context_.stream_manager.get_current_volume()));
	volume_slider_.vernier([](unsigned maximum, unsigned cursor_value)
	{
		return std::string(std::to_string(cursor_value) + "/" + std::to_string(maximum));
	});
	volume_slider_.events().value_changed([this]()
	{
		subject_.notify(volume_slider_, context_, events::Event::VolumeChanged);
	});
	search_textbox_.line_wrapped(true).multi_lines(false).tip_string("Search...");
	search_textbox_.events().text_changed([this]()
	{
		subject_.notify(search_textbox_, context_, events::Event::SearchStations);
	});
	container_.div(
		"<content vertical margin=[5%,0,0,0]" 
		"<first_line weight=12% arrange=[10%,10%,10%,10%] gap=1% margin=1%>"
		"<between_line weight=10% arrange=[49%,48%] gap=1% margin=1% >"
		"<second_line weight=8% arrange=[25%,72%] gap=1% margin=1%>"
		"<listbox margin=1%>"
		">");
	container_.field("first_line") << play_button_ << pause_button_ << mute_button_ ;
	container_.field("between_line") << current_station_label_ << current_song_label_;
	container_.field("second_line") << search_textbox_ << volume_slider_;
	container_.field("listbox") << stations_listbox_;
	container_.collocate();
}

void MainState::init_contextual_menus()
{
    song_label_menu_.append("Copy title to clipboard.", [this](auto&)
    {
        subject_.notify(current_song_label_, context_, events::Event::CopySongTitleToClipboard);
    });
    listbox_item_menu_.append("Play", [this](auto& )
    {
        subject_.notify(stations_listbox_, context_, events::Event::StreamNew);
    });
    listbox_item_menu_.append("Subscribe", [this](auto&)
    {
        subject_.notify(stations_listbox_, context_, events::Event::SubscribeToStation);
    });
    listbox_item_menu_.append("Delete from list", [this](auto&)
    {
        subject_.notify(stations_listbox_, context_, events::Event::DeleteStation);
    });
}

void MainState::init_listbox()
{
	stations_listbox_.append("User stations");
	stations_listbox_.append("Default stations");
	stations_listbox_.append_header("Station's name");
	stations_listbox_.append_header("Favorite");
	stations_listbox_.append_header("User defined");
	stations_listbox_.column_at(static_cast<std::size_t>(StationListboxColumns::Name)).width(300u);
	stations_listbox_.column_at(static_cast<std::size_t>(StationListboxColumns::Favorite)).width(50u);
	stations_listbox_.column_at(static_cast<std::size_t>(StationListboxColumns::UserDefined)).width(0u); // 0u to make this column invisibe to the user and so that we can check easly whether it is user defined etc.
	stations_listbox_.enable_single(true, false);
	subject_.notify(stations_listbox_, context_, events::Event::PopulateListbox);
	stations_listbox_.sort_col(cast_uint(StationListboxColumns::Favorite), true);
    stations_listbox_.events().mouse_up([this](const nana::arg_mouse& arg)
    {
        if (!arg.is_left_button() && !stations_listbox_.selected().empty() && !stations_listbox_.cast(arg.pos).empty() && !stations_listbox_.cast(arg.pos).is_category())
            subject_.notify(stations_listbox_, context_, events::Event::StationsListboxContextualMenu);        
    });
	stations_listbox_.events().dbl_click([this](const nana::arg_mouse& arg)
	{
		if(!stations_listbox_.cast(arg.pos).is_category()) // this condition must be fulfilled because when we click category it selects the last item in it so when we dbl_click category it works just as we would click last item in it
		{
			subject_.notify(stations_listbox_, context_, events::Event::StreamNew);
			subject_.notify(stations_listbox_, context_, events::Event::UpdateStationLabel);
			subject_.notify(stations_listbox_, context_, events::Event::UpdateSongLabel);
		}
	});
}

void MainState::update_titles()
{
	using namespace std::chrono_literals;
	current_song_label_.caption(context_.stream_manager.get_song_title());
	while(true)
	{
		std::this_thread::sleep_for(10s);
		std::lock_guard<std::mutex>{song_title_mutex_};
		subject_.notify(stations_listbox_, context_, events::Event::UpdateSongLabel);
	}
}
