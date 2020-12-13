#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>

[[nodiscard]] bool ends_with(std::string_view text, std::string_view ending);

[[nodiscard]] float volume_int_to_float(int vol) noexcept;
[[nodiscard]] unsigned int volume_float_to_int(float vol) noexcept;

[[nodiscard]] bool str_to_bool(const std::string& str) noexcept;
[[nodiscard]] std::string bool_to_str(bool b) noexcept;

void copy_to_clipboard(const std::string& message);

[[nodiscard]] char easytolower(char in) noexcept;

[[nodiscard]] std::string string_to_lower(const std::string& str);

[[nodiscard]] std::string replace_dollar_with_version_number(std::string_view text);

#endif