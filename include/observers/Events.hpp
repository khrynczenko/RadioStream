#ifndef EVENTS_HPP
#define EVENTS_HPP

namespace radiostream
{
    enum class Event
    {
        PauseClicked,
        PlayClicked,
        NewStationRequested,
		MuteClicked,
		VolumeChanged,

        AddStationToDatabase,
        DeleteStationFromDatabase,
        StationAddedToDatabase,
        StationDeletedFromDatabase,

        SearchStationsRequested,
        SearchLanguagesRequested,
        SearchCountriesRequested,

	    ConfigChangeLanguage,
        
        StationBeingPlayedChanged,
        StationSongHasChanged,
	};
}

#endif