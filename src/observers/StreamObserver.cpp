#include "../../include/observers/StreamObserver.hpp"
#include "../../include/Constants.hpp"
#include "../../include/Utilities.hpp"
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/button.hpp>
StreamObserver::StreamObserver(nana::slider& volume_slider, nana::button& mute_button)
	: volume_slider_(volume_slider)
	, mute_button_(mute_button)
{

}

void StreamObserver::on_notify(const nana::widget& caller, Context context, events::Event e)
{
	using namespace constants;
	switch(e)
	{
	case events::Event::StreamPause:
    {
        context.stream_manager.pause();
    }
    break;

	case events::Event::StreamPlay:
	{
        context.stream_manager.play();
	}
	break;

	case events::Event::VolumeChanged:
	{
        if (!mute_button_.pushed())
            context.stream_manager.set_current_volume(volume_int_to_float(static_cast<const nana::slider&>(caller).value()));
	}
	break;

	case events::Event::StreamNew:
	{
		const nana::listbox&  stations_listbox = static_cast<const nana::listbox&>(caller);
		if (!stations_listbox.selected().empty())
		{

			auto selected_item = stations_listbox.selected().front();
			std::string station_name;
			if (selected_item.cat == static_cast<std::size_t>(StationListboxCategories::Default))
			{
				station_name = stations_listbox.at(static_cast<std::size_t>(StationListboxCategories::Default)).at(selected_item.item).text(static_cast<std::size_t>(StationListboxColumns::Name));
			}
			else
			{
				station_name = stations_listbox.at(static_cast<std::size_t>(StationListboxCategories::UserDefined)).at(selected_item.item).text(static_cast<std::size_t>(StationListboxColumns::Name));
			}

			context.stream_manager.set_new_stream(context.stations_manager.get_station_ip(station_name));
			context.stream_manager.play();
		}
	}
	break;

	case events::Event::StreamMute:
    {
        if (context.stream_manager.get_current_volume() != 0.f)
        {
            context.stream_manager.set_current_volume(0.f);
            mute_button_.pushed(true);
        }
        else
        {
            context.stream_manager.set_current_volume(volume_int_to_float(volume_slider_.value()));
            mute_button_.pushed(false);
        }
    }
	break;

	}
}
