#ifndef EVENTS_HPP
#define EVENTS_HPP

namespace radiostream
{
    enum class Event
    {
        PauseClicked,
        PlayClicked,
        NewStationRequested,
        StationStartedPlaying,
        NewStationLoading,
        StationMuted,
        StationUnmuted,
		MuteClicked,
        MuteUnclicked,
		VolumeChanged,
        StationPaused,

        AddStationToDatabase,
        DeleteStationFromDatabase,
        StationAddedToDatabase,
        StationDeletedFromDatabase,

        SearchStationsRequested,
        SearchLanguagesRequested,
        SearchCountriesRequested,

        ConfigApplyNewChanges,
        
        NewStationSet,
        StationSongHasChanged,
        StreamLoadingError
	};
}

#endif