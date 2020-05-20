#ifndef STREAMMANGER_HPP
#define STREAMMANGER_HPP

// Fix for the problem on windows when including windows.h before winsock2.h
#define WIN32_LEAN_AND_MEAN
#define _WINSOCKAPI_

#pragma warning(push, 0)
#include <bass.h>
#pragma warning(pop)
#include <string>
#include <mutex>
#include <optional>
#include <map>

/**
 * \brief StreamManager is responsible for creating the stream, associating it
 * with the channel and managing it, it mean changing volume, pausing, playing
 * associating with URL etc.
 */

using BassErrorCode = int;
using BassErrorMessage = std::string;

extern const std::map<BassErrorCode, BassErrorMessage> ERROR_CODES_AND_MESSAGES;

class StreamManager {
   public:
    void mute();
    void unmute();
    void set_current_volume(float);
    [[nodiscard]] float get_current_volume() const noexcept;
    [[nodiscard]] std::optional<BassErrorCode> set_stream(
        const std::string& url);
    void pause();
    void play();
    [[nodiscard]] std::string get_song_title() const;
    StreamManager();

   private:
    HSTREAM main_stream_;
    bool muted_;
    float current_volume_;
    std::string url_playing_;
    std::mutex mutex_;
};

#endif
