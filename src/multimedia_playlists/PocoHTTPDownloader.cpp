#include "../../include/multimedia_playlists/PocoHTTPDownloader.hpp"
#include <Poco/Net/FTPClientSession.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/URIStreamOpener.h>
#include <Poco/StreamCopier.h>
#include <Poco/URI.h>
#include <Poco/Net/HTTPStreamFactory.h>
#include <memory>
#include <sstream>

std::string PocoHTTPDownloader::download(std::string_view url) const
{
    const Poco::URI uri(std::string{url});
    std::stringstream url_to_return;
    Poco::Net::HTTPStreamFactory sfac{};
    std::unique_ptr<std::istream> pStr(sfac.open(uri));
    Poco::StreamCopier::copyStream(*pStr, url_to_return);
    return url_to_return.str();
}
