#include "../include/Utilities.hpp"
#include <algorithm>
#include <stdexcept>


bool ends_with(std::string_view text, std::string_view ending)
{
    return text.substr(text.size() - ending.size(), ending.size()) == ending;
}

float volume_int_to_float(int vol) noexcept
{
	return static_cast<float>(vol) / 100.f;
}

unsigned int volume_float_to_int(float vol) noexcept
{
	return static_cast<unsigned int>(vol*100.f);
}

char easytolower(char in) noexcept {
    if (in <= 'Z' && in >= 'A')
    {
        return in - ('Z' - 'z');
    }
    return in;
}

std::string string_to_lower(const std::string& str)
{
    std::string lowered;
    lowered.resize(str.size());
    std::transform(str.begin(), str.end(), lowered.begin(), easytolower);
    return lowered;
}

