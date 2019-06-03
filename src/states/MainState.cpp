#include "../../include/states/MainState.hpp"
#include "../../include/Constants.hpp"
#include "../../include/Utilities.hpp"
#include "../../include/StationPlayer.hpp"
#include "../../include/exceptions/NanaTextboxProcessingException.hpp"
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/form.hpp>
#include <clip.h>

using namespace constants;

MainState::MainState(StatesManager& manager, Context& context)
    : State(manager, context)
    , container_(context.window_)
    , current_song_label_(context.window_, context.localizer_.get_localized_text("no song is playing"))
    , current_station_label_(context.window_, context.localizer_.get_localized_text("no station is playing"))
    , play_button_(context.window_)
    , pause_button_(context.window_)
    , mute_button_(context.window_)
    , search_textbox_(context.window_)
    , stations_listbox_(context.window_, context)
    , volume_slider_(context.window_)
{
    build_interface();
    init_contextual_menus();
    set_listbox_events();
    refresh_listbox();
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
    play_button_.caption(context_.localizer_.get_localized_text("Play"));
    play_button_.events().click([this]()
    {
        notify(Observer::placeholder, radiostream::Event::PlayClicked);
    });
    pause_button_.caption(context_.localizer_.get_localized_text("Pause"));
    pause_button_.events().click([this]()
    {
        notify(Observer::placeholder, radiostream::Event::PauseClicked);
    });
    mute_button_.caption(context_.localizer_.get_localized_text("Mute"));
    mute_button_.enable_pushed(true);
    mute_button_.events().mouse_up([this]()
    {
        if (mute_button_.pushed())
        {
            notify(std::make_any<unsigned int>(volume_slider_.value()), radiostream::Event::MuteClicked);
        }
        else
        {
            notify(std::make_any<unsigned int>(volume_slider_.value()), radiostream::Event::MuteUnclicked);
        }
    });
    volume_slider_.scheme().color_vernier = VERNIER_COLOR;
    volume_slider_.maximum(100);
    volume_slider_.value(volume_float_to_int(context_.station_player_.get_volume()));
    volume_slider_.vernier([](const unsigned int maximum, const unsigned int cursor_value)
    {
        return std::string(std::to_string(cursor_value) + "/" + std::to_string(maximum));
    });
    volume_slider_.events().value_changed([this]()
    {
        notify(std::make_any<unsigned int>(volume_slider_.value()), radiostream::Event::VolumeChanged);
    });
    search_textbox_.line_wrapped(true).multi_lines(false).tip_string("Search...");
    search_textbox_.events().text_changed([this]()
    {
        search_stations();
    });
    container_.div(
        "<content vertical margin=[5%,0,0,0]"
        "<buttons weight=12% arrange=[10%,10%,10%,10%] gap=1% margin=1%>"
        "<labels weight=10% arrange=[49%,48%] gap=1% margin=1% >"
        "<misc weight=8% arrange=[25%,72%] gap=1% margin=1%>"
        "<listbox margin=[1%,1%,7%,1%]>"
        ">");
    container_.field("buttons") << play_button_ << pause_button_ << mute_button_;
    container_.field("labels") << current_station_label_ << current_song_label_;
    container_.field("misc") << search_textbox_ << volume_slider_;
    container_.field("listbox") << stations_listbox_;
    container_.collocate();
}

void MainState::change_visibility(bool visible)
{
    container_.erase(context_.window_);
    container_.field_display("content", visible);
    context_.menubar_.show();
    container_.collocate();
}

void MainState::refresh_listbox()
{
   const auto& stations = context_.stations_database_.get_stations();
   stations_listbox_.populate_listbox(stations);
}

void MainState::station_being_played_changed(const Station& changed_station)
{
    current_station_label_.caption(changed_station.name_);
}

void MainState::song_has_changed(std::string_view song_title)
{
    current_song_label_.caption(std::string(song_title));
}

void MainState::init_contextual_menus()
{
    song_label_menu_.append(context_.localizer_.get_localized_text("Copy title to clipboard."), [this](auto&)
    {
        const auto title = current_song_label_.caption();
        clip::set_text(title);
    });
    listbox_item_menu_.append(context_.localizer_.get_localized_text("Play"), [this](auto&)
    {
        on_new_station_request();
    });
    listbox_item_menu_.append(context_.localizer_.get_localized_text("Copy name to clipboard"), [this](auto&)
    {
        copy_station_name_to_clipboard();
    });
    listbox_item_menu_.append(context_.localizer_.get_localized_text("Copy URL to clipboard"), [this](auto&)
    {
        copy_station_url_to_clipboard();
    });
    listbox_item_menu_.append(context_.localizer_.get_localized_text("Delete from list"), [this](auto&)
    {
        delete_station();
    });
}

void MainState::set_listbox_events()
{
    stations_listbox_.events().mouse_down([this](const nana::arg_mouse& arg)
    {
        if (!arg.is_left_button())
        {
            pop_stations_listbox_menu();
        }
    });
    stations_listbox_.events().dbl_click([this](const nana::arg_mouse& arg)
    {
        on_new_station_request();
    });
}

void MainState::search_stations()
{
    std::string string_to_find{};
    if (!search_textbox_.getline(0, string_to_find))
    {
        throw NanaTextboxProcessingException();
    }
    stations_listbox_.auto_draw(false);
    if (!string_to_find.empty())
    {
        stations_listbox_.clear();
        const auto& stations = context_.stations_database_.get_stations_by_substring(string_to_find);
        stations_listbox_.populate_listbox(stations);
    }
    else
    {
        refresh_listbox();
    }
    stations_listbox_.auto_draw(true);
}

void MainState::pop_song_title_menu()
{
    auto position = nana::API::cursor_position();
    nana::API::calc_window_point(context_.window_, position);
    song_label_menu_.popup(context_.window_, position.x, position.y);
}

void MainState::pop_stations_listbox_menu()
{
    auto position = nana::API::cursor_position();
    nana::API::calc_window_point(context_.window_, position);
    listbox_item_menu_.popup(context_.window_, position.x, position.y);
}

void MainState::copy_station_name_to_clipboard()
{
    Station station{};
    const auto index = stations_listbox_.selected().front();
    stations_listbox_.at(index.cat).at(index.item).resolve_to(station);
    clip::set_text(station.name_);
}

void MainState::copy_station_url_to_clipboard()
{
    Station station{};
    const auto index = stations_listbox_.selected().front();
    stations_listbox_.at(index.cat).at(index.item).resolve_to(station);
    clip::set_text(station.url_);
}

void MainState::delete_station()
{
    Station station{};
    const auto index = stations_listbox_.selected().front();
    stations_listbox_.at(index.cat).at(index.item).resolve_to(station);
    notify(std::make_any<Station>(station), radiostream::Event::DeleteStationFromDatabase);
}

void MainState::on_new_station_request()
{
    auto station = stations_listbox_.get_selected_station();
    if(station.has_value())
    {
        notify(station.value(), radiostream::Event::NewStationRequested);
    }
}

void MainState::on_notify(radiostream::Event e, const std::any &data)
{
    switch(e)
    {
        case radiostream::Event::NewStationSet:
        {
            const auto station = std::any_cast<Station>(data);
            station_being_played_changed(station);
        }
        break;
        case radiostream::Event::StationSongHasChanged:
        {
            song_has_changed(std::any_cast<std::string>(data));

        }
        case radiostream::Event::StationAddedToDatabase:
        {
            refresh_listbox();
        }
        break;
        case radiostream::Event::StationDeletedFromDatabase:
        {
            refresh_listbox();
        }
        break;
    }
}


