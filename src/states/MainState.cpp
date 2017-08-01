#include "../../include/states/MainState.hpp"
#include "../../include/observers/StreamObserver.hpp"
#include "../../include/Constants.hpp"
#include "../../include/Utilities.hpp"
#include "../../include/observers/StationsObserver.hpp"
#include <nana/gui/widgets/menubar.hpp>

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
	subject_.attach(std::make_unique<StreamObserver>());
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
        {
            pop_song_title_menu();
        }
    });
	play_button_.caption("Play");
    play_button_.events().click([this]()
    {
        subject_.notify(std::make_any<bool>(true), context_, events::Event::StreamPlay);
    });
	pause_button_.caption("Pause");
	pause_button_.events().click([this]()
	{
		subject_.notify(std::make_any<bool>(true), context_, events::Event::StreamPause);
	});
	mute_button_.caption("Mute");
    mute_button_.enable_pushed(true);
    mute_button_.events().mouse_up([this]()
    {
        if(mute_button_.pushed())
        {
            subject_.notify(std::make_any<unsigned>(volume_slider_.value()), context_, events::Event::StreamMute);
        }
        else
        {
            subject_.notify(std::make_any<unsigned>(volume_slider_.value()), context_, events::Event::VolumeChanged);
        }

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
        if (!mute_button_.pushed())
        {
            subject_.notify(std::make_any<unsigned>(volume_slider_.value()), context_, events::Event::VolumeChanged);
        }    
	});
	search_textbox_.line_wrapped(true).multi_lines(false).tip_string("Search...");
	search_textbox_.events().text_changed([this]()
	{
        search_stations();
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
        std::string title = current_song_label_.caption();
        copy_to_clipboard(title);
    });
    listbox_item_menu_.append("Play", [this](auto&)
    {
        set_new_stream();
    });
    listbox_item_menu_.append("Subscribe", [this](auto&)
    {
        subscribe_to_station();
    });
    listbox_item_menu_.append("Delete from list", [this](auto&)
    {
        delete_station();
    });
}

void MainState::init_listbox()
{
	stations_listbox_.append("User stations");
	stations_listbox_.append("Default stations");
	stations_listbox_.append_header("Station's name");
    stations_listbox_.append_header("Ip");
	stations_listbox_.append_header("Favorite");
	stations_listbox_.append_header("User defined");
	stations_listbox_.column_at(static_cast<std::size_t>(StationListboxColumns::Name)).width(300u);
    stations_listbox_.column_at(static_cast<std::size_t>(StationListboxColumns::Ip)).width(200u);
	stations_listbox_.column_at(static_cast<std::size_t>(StationListboxColumns::Favorite)).width(100u);
	stations_listbox_.column_at(static_cast<std::size_t>(StationListboxColumns::UserDefined)).width(0u); // 0u to make this column invisibe to the user and so that we can check easly whether it is user defined etc.
	stations_listbox_.enable_single(true, false);
    populate_listbox();
	stations_listbox_.sort_col(cast_uint(StationListboxColumns::Favorite), true);
    stations_listbox_.events().mouse_up([this](const nana::arg_mouse& arg)
    {
        if (!arg.is_left_button() && !stations_listbox_.selected().empty() && !stations_listbox_.cast(arg.pos).empty() && !stations_listbox_.cast(arg.pos).is_category())
            pop_stations_listbox_menu();
    });
	stations_listbox_.events().dbl_click([this](const nana::arg_mouse& arg)
	{
		if(!stations_listbox_.cast(arg.pos).is_category()) // this condition must be fulfilled because when we click category it selects the last item in it so when we dbl_click category it works just as we would click last item in it
		{
            set_new_stream();
            update_station_label();
            update_song_label();
		}
	});
}

void MainState::update_titles()
{
	using namespace std::chrono_literals;
    update_song_label();
	while(true)
	{
		std::this_thread::sleep_for(10s);
		std::lock_guard<std::mutex>{song_title_mutex_};
        update_song_label();
	}
}

void MainState::update_song_label()
{
    current_song_label_.caption(context_.stream_manager.get_song_title());
}

void MainState::update_station_label()
{
    if (!stations_listbox_.selected().empty())
    {
        auto selected_item = stations_listbox_.selected().front();
        if (selected_item.cat == static_cast<size_t>(StationListboxCategories::Default))
        {
            auto station_name = stations_listbox_.at(static_cast<size_t>(StationListboxCategories::Default)).at(selected_item.item).text(static_cast<size_t>(StationListboxColumns::Name));
            current_station_label_.caption(station_name);
        }
        else
        {
            auto station_name = stations_listbox_.at(static_cast<size_t>(StationListboxCategories::UserDefined)).at(selected_item.item).text(static_cast<size_t>(StationListboxColumns::Name));
            current_station_label_.caption(station_name);
        }
    }
}

void MainState::subscribe_to_station()
{
    //changes favorite value in both listbox and StationsManager::stations_
    auto selected_item = stations_listbox_.selected().front();
    if (selected_item.cat == static_cast<size_t>(StationListboxCategories::Default))
    {
        auto station_name = stations_listbox_.at(static_cast<size_t>(StationListboxCategories::Default)).at(selected_item.item).text(static_cast<size_t>(StationListboxColumns::Name));
        context_.stations_manager.set_favorite(station_name);
        bool past_favorite = str_to_bool(stations_listbox_.at(static_cast<size_t>(StationListboxCategories::Default)).at(selected_item.item).text(static_cast<size_t>(StationListboxColumns::Favorite)));
        stations_listbox_.at(static_cast<size_t>(StationListboxCategories::Default)).at(selected_item.item).text(static_cast<size_t>(StationListboxColumns::Favorite), bool_to_str(!past_favorite));
    }
    else
    {
        auto station_name = stations_listbox_.at(static_cast<size_t>(StationListboxCategories::UserDefined)).at(selected_item.item).text(static_cast<size_t>(StationListboxColumns::Name));
        context_.stations_manager.set_favorite(station_name);
        bool past_favorite = str_to_bool(stations_listbox_.at(static_cast<size_t>(StationListboxCategories::UserDefined)).at(selected_item.item).text(static_cast<size_t>(StationListboxColumns::Favorite)));
        stations_listbox_.at(static_cast<size_t>(StationListboxCategories::UserDefined)).at(selected_item.item).text(static_cast<size_t>(StationListboxColumns::Favorite), bool_to_str(!past_favorite));
    }
}

void MainState::populate_listbox()
{
    stations_listbox_.auto_draw(false);
    for (const auto& station : context_.stations_manager.get_stations())
    {
        if (station.user_defined_)
        {
            stations_listbox_.at(static_cast<nana::drawerbase::listbox::size_type>(StationListboxCategories::UserDefined)).append(station);
        }

        else
        {
            stations_listbox_.at(static_cast<nana::drawerbase::listbox::size_type>(StationListboxCategories::Default)).append(station);
        }
    }
    stations_listbox_.sort_col(cast_uint(StationListboxColumns::Favorite), true);
    stations_listbox_.auto_draw(true);
}

void MainState::search_stations()
{
    std::string searched_string{};
    search_textbox_.getline(0, searched_string);
    if (!searched_string.empty())
    {
        stations_listbox_.clear(cast_uint(StationListboxCategories::NanaDefault));
        stations_listbox_.clear(cast_uint(StationListboxCategories::Default));
        stations_listbox_.clear(cast_uint(StationListboxCategories::UserDefined));
        auto station_names = context_.stations_manager.search_matching_stations(searched_string);
        for (const auto& listed_station : context_.stations_manager.get_stations())
        {
            for (const auto& name : station_names)
            {
                if (listed_station.name_ == name)
                {
                    if (listed_station.user_defined_)
                        stations_listbox_.at(cast_uint(StationListboxCategories::UserDefined)).append(listed_station);
                    else
                        stations_listbox_.at(cast_uint(StationListboxCategories::Default)).append(listed_station);
                }
            }
        }
    }
    else
    {
        stations_listbox_.clear(cast_uint(StationListboxCategories::NanaDefault));
        stations_listbox_.clear(cast_uint(StationListboxCategories::Default));
        stations_listbox_.clear(cast_uint(StationListboxCategories::UserDefined));
        populate_listbox();
    }
}

void MainState::pop_song_title_menu()
{
    auto position = nana::API::cursor_position();
    nana::API::calc_window_point(context_.window, position);
    song_label_menu_.popup(context_.window, position.x, position.y);
}

void MainState::pop_stations_listbox_menu()
{
    auto position = nana::API::cursor_position();
    nana::API::calc_window_point(context_.window, position);
    listbox_item_menu_.popup(context_.window, position.x, position.y);
}

void MainState::set_new_stream()
{
    if (!stations_listbox_.selected().empty())
    {

        auto selected_item = stations_listbox_.selected().front();
        std::string station_name;
        if (selected_item.cat == static_cast<std::size_t>(StationListboxCategories::Default))
        {
            station_name = stations_listbox_.at(static_cast<std::size_t>(StationListboxCategories::Default)).at(selected_item.item).text(static_cast<std::size_t>(StationListboxColumns::Name));
        }
        else
        {
            station_name = stations_listbox_.at(static_cast<std::size_t>(StationListboxCategories::UserDefined)).at(selected_item.item).text(static_cast<std::size_t>(StationListboxColumns::Name));
        }
        subject_.notify(station_name, context_, events::Event::StreamNew);
    }
}

void MainState::delete_station()
{
    Station station{};
    auto indexes = stations_listbox_.selected().at(0);
    stations_listbox_.at(indexes.cat).at(indexes.item).resolve_to(station);
    subject_.notify(std::make_any<Station>(station), context_, events::Event::DeleteStation);
    populate_listbox();
}
