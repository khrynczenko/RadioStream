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
            std::this_thread::sleep_for(std::chrono::duration<int>(std::chrono::seconds(2)));
            check_if_song_title_has_changed();
        }
    });
    thread.detach();
}

void StationPlayer::mute()
{
    stream_manager_.mute();
    notify(Observer::placeholder, radiostream::Event::StationMuted);
}

void StationPlayer::unmute()
{
    stream_manager_.unmute();
    notify(Observer::placeholder, radiostream::Event::StationUnmuted);
}

void StationPlayer::play()
{
    stream_manager_.play();
    notify(Observer::placeholder, radiostream::Event::StationStartedPlaying);
}

void StationPlayer::pause()
{
    stream_manager_.pause();
    notify(Observer::placeholder, radiostream::Event::StationPaused);
}

void StationPlayer::set_volume(float volume)
{
    stream_manager_.set_current_volume(volume);
    if (volume == 0.f)
    {
        notify(Observer::placeholder, radiostream::Event::StationMuted);
    }
}

float StationPlayer::get_volume() const noexcept
{
    return stream_manager_.get_current_volume();
}

bool StationPlayer::set_station(const Station& station)
{
    station_ = station;
    notify(Observer::placeholder, radiostream::Event::NewStationLoading);
    const auto& possible_error = stream_manager_.set_stream(station_.ip_);
    if (possible_error.has_value())
    {
        notify(std::make_any<BassErrorCode>(possible_error.value()), radiostream::Event::StreamLoadingError);
        return false;
    }
    notify(std::make_any<Station>(station_), radiostream::Event::NewStationSet);
    check_if_song_title_has_changed();
    return true;
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
