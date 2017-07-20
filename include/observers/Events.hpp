#ifndef EVENTS_HPP
#define EVENTS_HPP

namespace events
{
	enum class Event
	{
        //StreamObserver events
		StreamPause,
		StreamPlay,
		StreamNew,
		StreamMute,
		VolumeChanged,
        //MainStateObserver events
		UpdateStationLabel,
		SearchStations,
		PopulateListbox,
		UpdateSongLabel,
		SubscribeToStation,
	    StationsListboxContextualMenu,
	    CopySongTitleToClipboard,
	    SongLabelContextualMenu,
        //StationsObserver events
        AddStation,
        DeleteStation,
	};
}

#endif