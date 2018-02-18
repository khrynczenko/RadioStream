#include "../../include/exceptions/NanaTextboxProcessingException.hpp"

char const* NanaTextboxProcessingException::what() const noexcept
{
    return "Could not process textbox widget.";
}
