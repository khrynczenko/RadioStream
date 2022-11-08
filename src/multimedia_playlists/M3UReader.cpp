#include "../../include/multimedia_playlists/M3UReader.hpp"
#include "../../include/exceptions/ReaderCouldNotReadUrl.hpp"
#pragma warning(push, 0)
#include <Poco/URI.h>
#include <Poco/Exception.h>
#pragma warning(pop)

std::string M3UReader::get_station_url(std::istream& input) const {
    std::string read_line;
    while (!input.eof()) {
        std::getline(input, read_line);
        try {
            Poco::URI uri{read_line};
            if (uri.getScheme() == "http") {
                return uri.toString();
            }
            throw(Poco::SyntaxException("Wrong m3u url."));
        } catch ([[maybe_unused]] const Poco::SyntaxException& e) {
        }
    }
    throw ReaderCouldNotReadUrl();
}
