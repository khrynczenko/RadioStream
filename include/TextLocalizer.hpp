#ifndef TEXTLOCALIZER_HPP
#define TEXTLOCALIZER_HPP

#include "Language.hpp"
#include <nana/internationalization.hpp>
#include <array>
#include <experimental/filesystem>
#include <map>

using LanguageNativeName = std::string;

struct KeyComparator
{
    bool operator()(LanguageCode lhs, LanguageCode rhs) const noexcept;
};

extern const std::map<const LanguageCode, const LanguageNativeName, KeyComparator> LANGUAGES_CODES_AND_TRANSLATIONS;

class LanguagesPathsContainer
{
public:
    LanguagesPathsContainer() noexcept;
    std::experimental::filesystem::path get_path(LanguageCode lang);

private:
    std::map<const LanguageCode, const std::experimental::filesystem::path, KeyComparator> languages_filpaths_;
};

class TextLocalizer
{
public:
    TextLocalizer() noexcept;
    void switch_language(LanguageCode lang);
    template <typename ...Args>
    std::string get_localized_text(std::string text_id, Args ... args) const;
    std::string get_localized_text(std::string text_id) const;
private:
    nana::internationalization localizer_;
    LanguagesPathsContainer languages_;
};


template <typename ... Args>
std::string TextLocalizer::get_localized_text(std::string text_id, Args ... args) const
{
    return localizer_(text_id, args...);
}

#endif
