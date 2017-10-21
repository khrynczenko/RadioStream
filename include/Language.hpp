#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <string_view>


class LanguageCode : public std::string
{
public:
    explicit LanguageCode(std::string_view code);
};


#endif
