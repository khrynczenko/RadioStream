#include "../../include/observers/MainStateObserver.hpp"
#include <nana/gui/widgets/textbox.hpp>
#include "../../include/states/MainState.hpp"

MainStateObserver::MainStateObserver(MainState& ui)
	: Observer()
	, ui_(ui)
{
}

void MainStateObserver::on_notify(const nana::widget& caller, Context context, events::Event e)
{

	switch (e)
	{
	case events::Event::SEARCH_STATIONS:
	{
		std::string searched_string{};
		const auto& textbox = static_cast<const nana::textbox&>(caller);
		textbox.getline(0, searched_string);
		if (!searched_string.empty())
		{
			ui_.stations_listbox_.clear(0);
			auto station_names = context.stations_manager.search_matching_stations(searched_string);
			for (const auto& listed_station : context.stations_manager.get_default_stations())
			{
				for (const auto& name : station_names)
				{
					if (listed_station.name_ == name)
					{
						ui_.stations_listbox_.at(0).append(name);
					}
				}
			}
		}
		else
		{
			ui_.stations_listbox_.clear(0);
			on_notify(ui_.stations_listbox_, context, events::Event::POPULATE_LISTBOX);
		}
	}
	break;
	case events::Event::POPULATE_LISTBOX:
	{
		ui_.stations_listbox_.auto_draw(false);
		for (const auto& station : context.stations_manager.get_default_stations())
		{
			ui_.stations_listbox_.at(0).append({ station.name_ });
		}
		ui_.stations_listbox_.auto_draw(true);
	}
	break;
	case events::Event::UPDATE_STATION_LABEL:
	{
		if (!ui_.stations_listbox_.selected().empty())
		{
			auto selected_item = ui_.stations_listbox_.selected().at(0);
			auto station_name = ui_.stations_listbox_.at(0).at(selected_item.item).text(0);
			ui_.current_station_label_.caption(ui_.stations_listbox_.at(0).at(selected_item.item).text(0));
		}
	}
	break;
	case events::Event::UPDATE_SONG_LABEL:
	{
		ui_.current_song_label_.caption(context.stream_manager.get_song_title());
	}
	break;
	}
}
