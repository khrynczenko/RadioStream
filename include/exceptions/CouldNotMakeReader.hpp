#ifndef RADIOSTREAM_COULDNOTMAKEREADER_HPP
#define RADIOSTREAM_COULDNOTMAKEREADER_HPP

#include <exception>

class CouldNotMakeReader : public std::exception
{
public:
    const char* what() const noexcept override;
};

#endif //RADIOSTREAM_COULDNOTMAKEREADER_HPP
