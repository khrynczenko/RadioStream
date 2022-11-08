#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <string>

class LanguageCode {
   public:
    LanguageCode() = default;
    explicit LanguageCode(std::string_view code);
    [[nodiscard]] bool operator==(const LanguageCode& rhs) const noexcept;
    [[nodiscard]] std::string as_string() const;

   private:
    std::string code_;
};

struct LanguageCodeComparator {
    [[nodiscard]] bool operator()(const LanguageCode& lhs, const LanguageCode& rhs) const noexcept;
};

#endif
