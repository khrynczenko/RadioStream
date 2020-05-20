#ifndef RADIOSTREAM_URIRESOLVER_HPP
#define RADIOSTREAM_URIRESOLVER_HPP

#include "../include/multimedia_playlists/HTTPDownloader.hpp"
#pragma warning(push, 0)
#include <Poco/URI.h>
#pragma warning(pop)
#include <memory>
#include <optional>

/**
 * Resolve URI i.e. there may exists URIs that point directly to a stream or
 * they could point to the Playlist file such as .m3u or .pls file. This class
 * solves this problem. In case its playlits it downlaods the files, parses it
 * and then produces direct URI if everything worked.
 */
class StreamURIResolver {
   public:
    explicit StreamURIResolver(
        std::unique_ptr<HTTPDownloader> downloader) noexcept;
    /**
     * Does the resolvement to URI which points directly to the stream.
     * @param uri Some URI.
     * @return If possible URI that points directly to the stream.
     */
    [[nodiscard]] std::optional<Poco::URI> resolve_uri(
        const Poco::URI& uri) const;
    [[nodiscard]] bool is_direct_uri(const Poco::URI& uri) const;

   private:
    std::unique_ptr<HTTPDownloader> downloader_;
};

#endif  // RADIOSTREAM_URIRESOLVER_HPP
