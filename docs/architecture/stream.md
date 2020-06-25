# Stream playback
All stream related stuff is handled by `bass` library and
wrapped for convienience in `StreamManager` and
`StationPlayer` classes.


```c++
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
};

class StationPlayer : public Subject {
   public:
    StationPlayer();
    void mute();
    void unmute();
    void play();
    void pause();
    void set_volume(float volume);
    float get_volume() const noexcept;
    [[nodiscard]] bool set_station(const Station& station);
    [[nodiscard]] Station get_station() const;
    [[nodiscard]] std::string get_song_title() const;
};
```