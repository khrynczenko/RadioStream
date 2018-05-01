#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <string>

class LanguageCode
{
public:
    LanguageCode() = default;
    explicit LanguageCode(std::string_view code);
    bool operator==(const LanguageCode& rhs) const noexcept;
    std::string as_string() const;
private:
    std::string code_;
};



#endif
