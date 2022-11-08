#include "../include/Station.hpp"
#include "../include/Utilities.hpp"

Station::Station(std::string_view name, std::string_view url, std::string_view country,
                 std::string_view language, std::string_view codec, std::string_view bitrate,
                 std::string_view tags)
    : name_(name),
      url_(url),
      country_(country),
      language_(language),
      codec_(codec),
      bitrate_(bitrate),
      tags_(tags) {}

bool Station::operator==(const Station& rhs) const noexcept {
    return (name_ == rhs.name_ && url_ == rhs.url_);
}

nana::listbox::oresolver& operator<<(nana::listbox::oresolver& ores, const Station& station) {
    return ores << station.name_ << station.url_ << station.country_ << station.language_
                << station.codec_ << station.bitrate_ << station.tags_;
}

nana::listbox::iresolver& operator>>(nana::listbox::iresolver& ires, Station& station) {
    return ires >> station.name_ >> station.url_ >> station.country_ >> station.language_ >>
           station.codec_ >> station.bitrate_ >> station.tags_;
}
