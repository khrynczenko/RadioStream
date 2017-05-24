#ifndef STREAMMANGER_HPP
#define STREAMMANGER_HPP
#include <bass.h>
#include <string>

class StreamManager
{
public:
	void set_volume(float);
	float get_volume() const;
	void set_new_stream(const std::string& url);
	void pause();
	void play();
	std::string get_song_title() const;
	StreamManager();
	~StreamManager() = default;
private:
	HSTREAM main_stream;
	float volume;
};

#endif
