#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <string>

float volume_int_to_float(int vol);
unsigned int volume_float_to_int(float vol);
template <typename T>
unsigned int cast_uint(T t);

bool str_to_bool(const std::string& str);
std::string bool_to_str(bool b);
template <typename T>
unsigned int cast_uint(T t)
{
	static_assert(std::is_integral<T>::value || std::is_enum<T>::value , "Cannot convert non integral to unsigned int");
	return static_cast<unsigned int>(t);
}

#endif