#ifndef STREAMMANGER_HPP
#define STREAMMANGER_HPP

//Fix for the problem on windows when including windows.h before winsock2.h
#define WIN32_LEAN_AND_MEAN
#define _WINSOCKAPI_

#include <bass.h>
#include <string>
#include <mutex>

/**
 * \brief StreamManager is responsible for creating the stream, associating it with the channel and managing it, it mean changing volume, pausing, playing associating with URL etc.
 */
class StreamManager
{
public:
	void set_current_volume(float);
	float get_current_volume() const noexcept;
	void set_stream(const std::string& url);
	void pause();
	void play();
	std::string get_song_title() const;
	StreamManager();
	~StreamManager() = default;
private:
	HSTREAM main_stream_;
	float current_volume_;
    std::string url_playing_;
    std::mutex mutex_;
};

#endif
