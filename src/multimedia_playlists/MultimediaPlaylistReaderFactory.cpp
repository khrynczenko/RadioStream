#include "../../include/multimedia_playlists/MultimediaPlaylistReaderFactory.hpp"
#include "../../include/Utilities.hpp"
#include "../../include/multimedia_playlists/PLSReader.hpp"
#include "../../include/multimedia_playlists/M3UReader.hpp"

std::unique_ptr<MultimediaPlaylistReader> MultimediaPlaylistReaderFactory::make_reader(Poco::URI uri)
{
    const std::string& path = uri.getPath();
    if (ends_with(path, ".pls"))
    {
        return std::make_unique<PLSReader>();
    }
    else if (ends_with(path, ".m3u"))
    {
        return std::make_unique<M3UReader>();
    }
    throw;
}
