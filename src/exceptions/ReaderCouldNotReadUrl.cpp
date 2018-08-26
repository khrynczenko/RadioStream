#include "../../include/exceptions/ReaderCouldNotReadUrl.hpp"

const char *ReaderCouldNotReadUrl::what() const noexcept {
    return "Url was not found where reading the stream.";
}
