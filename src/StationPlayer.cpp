#include "../include/StationPlayer.hpp"
#include <iostream>
#include <thread>

StationPlayer::StationPlayer()
    : current_song_title_("")
{
    auto thread = std::thread([this]()
    {
        while(true)
        {
            std::this_thread::sleep_for(std::chrono::duration<int>(std::chrono::seconds(5)));
            check_if_song_title_has_changed();
        }
    });
    thread.detach();
}

void StationPlayer::play()
{
    auto thread = std::thread([this]()
    {
        stream_manager_.play();
    });
    thread.detach();
}

void StationPlayer::pause()
{
    auto thread = std::thread([this]()
    {
        stream_manager_.pause();
    });
    thread.detach();
}

void StationPlayer::set_volume(float volume)
{
    stream_manager_.set_current_volume(volume);
}

float StationPlayer::get_volume() const noexcept
{
    return stream_manager_.get_current_volume();
}

void StationPlayer::set_station(const Station& station)
{
    station_ = station;
    auto thread = std::thread([this]()
    {
        stream_manager_.set_stream(station_.ip_);
        check_if_song_title_has_changed();
        notify(std::make_any<Station>(station_), radiostream::Event::StationBeingPlayedChanged);
    });
    thread.detach();
}

std::string StationPlayer::get_song_title() const
{
    return stream_manager_.get_song_title();
}

void StationPlayer::check_if_song_title_has_changed()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(stream_manager_.get_song_title() != current_song_title_)
    {
        current_song_title_ = stream_manager_.get_song_title();
        notify(std::make_any<std::string>(current_song_title_), radiostream::Event::StationSongHasChanged);
    }
}

Station StationPlayer::get_station() const
{
    return station_;
}
