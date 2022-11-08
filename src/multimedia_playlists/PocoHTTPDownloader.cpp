#include "../../include/multimedia_playlists/PocoHTTPDownloader.hpp"
#pragma warning(push, 0)
#include <Poco/Net/FTPClientSession.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/URIStreamOpener.h>
#include <Poco/StreamCopier.h>
#include <Poco/URI.h>
#include <Poco/Net/HTTPStreamFactory.h>
#pragma warning(pop)
#include <memory>
#include <sstream>

PocoHTTPDownloader::PocoHTTPDownloader() { Poco::Net::HTTPStreamFactory::registerFactory(); }

std::string PocoHTTPDownloader::download(std::string_view url) const {
    const Poco::URI uri(std::string{url});
    std::stringstream url_to_return;
    std::unique_ptr<std::istream> pStr(Poco::URIStreamOpener::defaultOpener().open(uri));
    Poco::StreamCopier::copyStream(*pStr, url_to_return);
    return url_to_return.str();
}
