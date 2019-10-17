#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>

bool ends_with(std::string_view text, std::string_view ending);

float volume_int_to_float(int vol) noexcept;
unsigned int volume_float_to_int(float vol) noexcept;

bool str_to_bool(const std::string& str) noexcept;
std::string bool_to_str(bool b) noexcept;

void copy_to_clipboard(const std::string& message);

char easytolower(char in) noexcept;

std::string string_to_lower(const std::string& str);

std::string replace_dollar_with_version_number(std::string_view text);

#endif