#include "../../include/states/MainState.hpp"
#include "../../include/Constants.hpp"
#include "../../include/Utilities.hpp"
#include "../../include/StationPlayer.hpp"
#include "../../include/exceptions/NanaTextboxProcessingException.hpp"
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/form.hpp>

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
    , stations_listbox_(context.window_)
    , volume_slider_(context.window_)
    , song_label_menu_()
    , listbox_item_menu_()
{
    build_interface();
    init_contextual_menus();
    init_listbox();
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
    volume_slider_.vernier([](unsigned int maximum, unsigned int cursor_value)
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

void MainState::set_station_name(const std::string& name)
{
    current_station_label_.caption(name);
}

void MainState::refresh_listbox()
{
    populate_listbox();
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
        std::string title = current_song_label_.caption();
        copy_to_clipboard(title);
    });
    listbox_item_menu_.append(context_.localizer_.get_localized_text("Play"), [this](auto&)
    {
        set_new_station();
    });
    listbox_item_menu_.append(context_.localizer_.get_localized_text("Delete from list"), [this](auto&)
    {
        delete_station();
    });
}

void MainState::init_listbox()
{
    stations_listbox_.append_header(context_.localizer_.get_localized_text("Station's name"));
    stations_listbox_.append_header(context_.localizer_.get_localized_text("URL"));
    stations_listbox_.append_header(context_.localizer_.get_localized_text("Country"));
    stations_listbox_.append_header(context_.localizer_.get_localized_text("Language"));
    stations_listbox_.append_header(context_.localizer_.get_localized_text("Codec"));
    stations_listbox_.append_header(context_.localizer_.get_localized_text("Bitrate"));
    stations_listbox_.append_header(context_.localizer_.get_localized_text("Tags"));
    stations_listbox_.column_at(static_cast<std::size_t>(StationListboxColumns::Name)).width(300u);
    stations_listbox_.column_at(static_cast<std::size_t>(StationListboxColumns::Url)).width(200u);
    stations_listbox_.column_at(static_cast<std::size_t>(StationListboxColumns::Country)).width(50u);
    stations_listbox_.column_at(static_cast<std::size_t>(StationListboxColumns::Language)).width(50u);
    stations_listbox_.column_at(static_cast<std::size_t>(StationListboxColumns::Codec)).width(20u);
    stations_listbox_.column_at(static_cast<std::size_t>(StationListboxColumns::Bitrate)).width(20u);
    stations_listbox_.column_at(static_cast<std::size_t>(StationListboxColumns::Tags)).width(100u);
    populate_listbox();
    stations_listbox_.enable_single(false, false);

    stations_listbox_.events().mouse_down([this](const nana::arg_mouse& arg)
    {
        sticky_select(arg);
        if (!arg.is_left_button())
        {
            pop_stations_listbox_menu();
        }
    });
    stations_listbox_.events().dbl_click([this](const nana::arg_mouse& arg)
    {
        if (!stations_listbox_.cast(arg.pos).is_category() && arg.is_left_button()) // this condition must be fulfilled because when we click category it selects the last item in it so when we dbl_click category it works just as we would click last item in it
        {
            set_new_station();
        }
    });
    stations_listbox_.auto_draw(true);
}

void MainState::populate_listbox()
{
    stations_listbox_.auto_draw(false);
    stations_listbox_.clear();
    for (const auto& station : context_.stations_database_.get_stations())
    {
        const auto category_index = static_cast<std::size_t>(StationListboxCategories::NanaDefault);
        stations_listbox_.at(category_index).append(station);
    }
    stations_listbox_.auto_draw(true);
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
        auto station_names_containing_substring = context_.stations_database_.get_stations_names_with_substring(string_to_find);
        const auto& all_stations = context_.stations_database_.get_stations();
        for (const auto& station : all_stations)
        {
            for (const auto& name : station_names_containing_substring)
            {
                if (string_to_lower(station.name_) == name)
                {
                    const auto category_index = static_cast<std::size_t>(StationListboxCategories::NanaDefault);
                    stations_listbox_.at(category_index).append(station);
                }
            }
        }
    }
    else
    {
        stations_listbox_.clear();
        populate_listbox();
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

void MainState::set_new_station()
{

    if (!stations_listbox_.selected().empty())
    {
        const auto selected_item = stations_listbox_.selected().front();
        const auto category_index = static_cast<std::size_t>(StationListboxCategories::NanaDefault);
        const auto column_index = static_cast<std::size_t>(StationListboxColumns::Name);
        const auto station_category = stations_listbox_.at(category_index);
        const auto name = station_category.at(selected_item.item).text(column_index);
        const auto url = station_category.at(selected_item.item).text(static_cast<std::size_t>(StationListboxColumns::Url));
        const auto country = station_category.at(selected_item.item).text(static_cast<std::size_t>(StationListboxColumns::Country));
        const auto language = station_category.at(selected_item.item).text(static_cast<std::size_t>(StationListboxColumns::Language));
        const auto codec = station_category.at(selected_item.item).text(static_cast<std::size_t>(StationListboxColumns::Codec));
        const auto bitrate = station_category.at(selected_item.item).text(static_cast<std::size_t>(StationListboxColumns::Bitrate));
        const auto tags = station_category.at(selected_item.item).text(static_cast<std::size_t>(StationListboxColumns::Tags));
        notify(Station{ name, url, country, language, codec, bitrate, tags}, radiostream::Event::NewStationRequested);
    }
}

void MainState::delete_station()
{
    Station station{};
    const auto index = stations_listbox_.selected().front();
    stations_listbox_.at(index.cat).at(index.item).resolve_to(station);
    notify(std::make_any<Station>(station), radiostream::Event::DeleteStationFromDatabase);
}

void MainState::sticky_select(const nana::arg_mouse & mouse)
{
    if (!stations_listbox_.selected().empty())
    {
        for (const auto& pair : stations_listbox_.selected())
        {
            if (pair.item == stations_listbox_.selected().front().item)
            {
                continue;
            }
            else
            {
                stations_listbox_.at(pair.cat).at(pair.item).select(false);
            }
        }
    }
}

