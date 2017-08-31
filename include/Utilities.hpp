#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>

float volume_int_to_float(int vol);
unsigned int volume_float_to_int(float vol);

bool str_to_bool(const std::string& str);
std::string bool_to_str(bool b);

void copy_to_clipboard(const std::string& message);

char easytolower(char in);

std::string string_to_lower(const std::string& str);
#endif