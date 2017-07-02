#include "../../include/observers/StreamObserver.hpp"
#include <nana/gui/widgets/listbox.hpp>
#include "../../include/Constants.hpp"

void StreamObserver::on_notify(const nana::widget& caller, Context context, events::Event e)
{
	using namespace constants;
	switch(e)
	{
	case events::Event::STREAM_PAUSE:
		context.stream_manager.pause();
		break;
	case events::Event::STREAM_PLAY:
		context.stream_manager.play();
		break;
	case events::Event::VOLUME_CHANGED:
		context.stream_manager.set_volume(volume_int_to_float(static_cast<const nana::slider&>(caller).value()));
		break;
	case events::Event::STREAM_NEW:
		const nana::listbox&  stations_listbox = static_cast<const nana::listbox&>(caller);
		if (!stations_listbox.selected().empty())
		{
			auto selected_item = stations_listbox.selected().front();
			std::string station_name = "";
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
		break;
	}
}
