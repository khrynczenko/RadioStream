#include "../include/StreamURIResolver.hpp"
#include "../include/Utilities.hpp"
#include "../include/multimedia_playlists/MultimediaPlaylistReaderFactory.hpp"
#include "../include/exceptions/ReaderCouldNotReadUrl.hpp"
#pragma warning(push, 0)
#include <Poco/Exception.h>
#pragma warning(pop)
#include <sstream>

StreamURIResolver::StreamURIResolver(
    std::unique_ptr<HTTPDownloader> downloader) noexcept
    : downloader_(std::move(downloader)) {}

std::optional<Poco::URI> StreamURIResolver::resolve_uri(
    const Poco::URI &uri) const {
    if (is_direct_uri(uri)) {
        return uri;
    } else {
        try {
            std::stringstream playlist_data{
                downloader_->download(uri.toString())};
            const auto reader =
                MultimediaPlaylistReaderFactory::make_reader(uri);
            const auto direct_uri = reader->get_station_url(playlist_data);
            return Poco::URI(direct_uri);
        } catch ([[maybe_unused]] const Poco::UnknownURISchemeException &e) {
            return std::nullopt;
        } catch ([[maybe_unused]] ReaderCouldNotReadUrl &e) {
            return std::nullopt;
        }
    }
}

bool StreamURIResolver::is_direct_uri(const Poco::URI &uri) const {
    const auto uri_as_string = uri.toString();
    if (ends_with(uri_as_string, ".pls") || ends_with(uri_as_string, ".m3u") ||
        ends_with(uri_as_string, ".m3u8")) {
        return false;
    }
    return true;
}
