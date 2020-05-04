#ifndef STATIONPLAYER_HPP
#define STATIONPLAYER_HPP

#include "StreamManager.hpp"
#include "Station.hpp"
#include "Subject.hpp"
#include <mutex>

class StationPlayer : public Subject {
   public:
    StationPlayer();
    void mute();
    void unmute();
    void play();
    void pause();
    void set_volume(float volume);
    float get_volume() const noexcept;
    bool set_station(const Station& station);
    Station get_station() const;
    std::string get_song_title() const;

   private:
    void check_if_song_title_has_changed();
    Station station_;
    StreamManager stream_manager_;
    std::string current_song_title_;
    std::mutex mutex_;
};

#endif