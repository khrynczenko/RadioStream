#ifndef EVENTS_HPP
#define EVENTS_HPP

namespace events
{
	enum class Event
	{
		StreamPause,
		StreamPlay,
		StreamSetNewByName,
        StreamSetNewByIP,
		StreamMute,
		StreamVolumeChanged,

        AddStation,
        DeleteStation,

	    ConfigChangeLanguage	
	};
}

#endif