#include "../../include/multimedia_playlists/PLSReader.hpp"
#include "../../include/exceptions/ReaderCouldNotReadUrl.hpp"

std::string PLSReader::get_station_url(std::istream& input) const {
    std::string read_line;
    while (!input.eof()) {
        std::getline(input, read_line);
        if (const std::size_t pos = read_line.find("File1"); pos != std::string::npos) {
            return read_line.substr(pos + 6, read_line.size() - (pos + 6));
        }
    }
    throw ReaderCouldNotReadUrl();
}
