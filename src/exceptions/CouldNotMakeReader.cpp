#include "../../include/exceptions/CouldNotMakeReader.hpp"

const char* CouldNotMakeReader::what() const noexcept {
    return "Unable to create reader for file";
}
