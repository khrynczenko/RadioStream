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
        //StatusObserver events
        LoadingStreamStatus,
        NormalStatus,
        SearchingStationsStatus,
        //StationsObserver events
        AddStation,
        DeleteStation,    
	};
}

#endif