#ifndef EVENTS_HPP
#define EVENTS_HPP

namespace radiostream
{
    enum class Event
    {
        StreamPause,
        StreamPlay,
        StreamSetNewStation,
		StreamMute,
		StreamVolumeChanged,

        AddStation,
        DeleteStation,

	    ConfigChangeLanguage,
        
        StationBeingPlayedChanged,
        StationSongHasChanged
	};
}

#endif