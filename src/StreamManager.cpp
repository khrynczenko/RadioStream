#include "../include/StreamManager.hpp"
#include <iostream>



void StreamManager::set_current_volume(float volume)
{
	BASS_ChannelSetAttribute(main_stream_, BASS_ATTRIB_VOL, volume);
	current_volume_ = volume;
}

float StreamManager::get_current_volume() const
{
	float value;
	BASS_ChannelGetAttribute(main_stream_, BASS_ATTRIB_VOL, &value);
	return value;
}

void StreamManager::set_new_stream(const std::string& url)
{
    url_playing_ = url;
	BASS_ChannelStop(main_stream_);
	BASS_StreamFree(main_stream_);
	main_stream_ = BASS_StreamCreateURL(url.c_str(), 0, 0, 0, 0);
	BASS_ChannelSetAttribute(main_stream_, BASS_ATTRIB_VOL, current_volume_);
}

void StreamManager::pause()
{
	BASS_ChannelStop(main_stream_);
    BASS_StreamFree(main_stream_);
    main_stream_ = NULL;
}

void StreamManager::play()
{
    
    if(main_stream_ == NULL)
    {
        main_stream_ = BASS_StreamCreateURL(url_playing_.c_str(), 0, 0, 0, 0);
        BASS_ChannelSetAttribute(main_stream_, BASS_ATTRIB_VOL, current_volume_);
    }
	BASS_ChannelPlay(main_stream_, true);
}

std::string StreamManager::get_song_title() const
{
	auto tags = BASS_ChannelGetTags(main_stream_, BASS_TAG_META);
	if (tags != nullptr)
	{
		//string in tags looks something like "StreamTitle='title',url='url'"
		std::cout << tags;
		std::string str = tags;
		unsigned first = str.find('\'');
		first++;
		unsigned last = str.substr(first).find('\'');
		return str.substr(first, last);
	}
	return "";
}

StreamManager::StreamManager()
	: main_stream_()
	, current_volume_(1.f)
    , url_playing_()
{
	if(!BASS_Init(-1, 44100, BASS_DEVICE_STEREO, nullptr, nullptr))
	{
		throw std::exception("Could not initialize sound device.");
	}
}


