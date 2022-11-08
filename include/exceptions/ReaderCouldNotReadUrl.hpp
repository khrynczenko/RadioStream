#ifndef RADIOSTREAM_READERCOULDNOTREADURL_HPP
#define RADIOSTREAM_READERCOULDNOTREADURL_HPP

#include <exception>
#include <string>

class ReaderCouldNotReadUrl : public std::exception {
   public:
    [[nodiscard]] const char* what() const noexcept override;
};

#endif  // RADIOSTREAM_READERCOULDNOTREADURL_HPP
