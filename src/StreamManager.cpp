#include "../include/StreamManager.hpp"
#include <stdexcept>
#include <iostream>

void StreamManager::mute()
{
	BASS_ChannelSetAttribute(main_stream_, BASS_ATTRIB_VOL, 0.f);
    muted_ = true;
}

void StreamManager::unmute()
{
	BASS_ChannelSetAttribute(main_stream_, BASS_ATTRIB_VOL, current_volume_);
    muted_ = false;
}

void StreamManager::set_current_volume(float volume)
{
    current_volume_ = volume;
    if (!muted_)
    {
        BASS_ChannelSetAttribute(main_stream_, BASS_ATTRIB_VOL, volume);
    }
}

float StreamManager::get_current_volume() const noexcept
{
    return current_volume_;
}

std::optional<BassErrorCode> StreamManager::set_stream(const std::string& url)
{
    std::lock_guard<std::mutex> lock(mutex_);
    url_playing_ = url;
    if(main_stream_ != 0)
    {
        BASS_ChannelStop(main_stream_);
        BASS_StreamFree(main_stream_);
    }
	main_stream_ = BASS_StreamCreateURL(url.c_str(), 0, 0, nullptr, nullptr);
    BassErrorCode possible_error = BASS_ErrorGetCode();
	BASS_ChannelSetAttribute(main_stream_, BASS_ATTRIB_VOL, current_volume_);
    
    if (main_stream_ == 0)
        return std::make_optional<BassErrorCode>(possible_error);
    return std::nullopt;
}

void StreamManager::pause()
{
    std::lock_guard<std::mutex> lock(mutex_);
	BASS_ChannelStop(main_stream_);
    BASS_StreamFree(main_stream_);
    main_stream_ = 0;
}

void StreamManager::play()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(main_stream_ == 0)
    {
        main_stream_ = BASS_StreamCreateURL(url_playing_.c_str(), 0, 0, nullptr, nullptr);
        BASS_ChannelSetAttribute(main_stream_, BASS_ATTRIB_VOL, current_volume_);
    }
	BASS_ChannelPlay(main_stream_, false);
}

std::string StreamManager::get_song_title() const
{
    const auto tags = BASS_ChannelGetTags(main_stream_, BASS_TAG_META);
	if (tags != nullptr)
	{
		//string in tags looks something like "StreamTitle='title',url='url'"
		std::string str = tags;
		auto first = str.find('\'');
		first++;
	    const auto last = str.substr(first).find('\'');
		return str.substr(first, last);
	}
	return "";
}

StreamManager::StreamManager()
	: main_stream_()
    , muted_(false)
	, current_volume_(1.f)
{
	if(!BASS_Init(-1, 44100, BASS_DEVICE_STEREO, nullptr, nullptr))
	{
		throw std::runtime_error("Could not initialize sound device.");
	}
}


