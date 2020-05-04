#ifndef TEXTLOCALIZER_HPP
#define TEXTLOCALIZER_HPP

#include "Language.hpp"
#pragma warning (push, 0)
#include <nana/internationalization.hpp>
#pragma warning (pop)
#include <array>
#include <filesystem>
#include <map>

class LanguagesPathsContainer
{
public:
    explicit LanguagesPathsContainer(const std::filesystem::path& lang_root_directory) noexcept;
    std::filesystem::path get_path(LanguageCode lang);

private:
    std::map<const LanguageCode, const std::filesystem::path, LanguageCodeComparator> languages_filepaths;
};

class TextLocalizer
{
public:
    explicit TextLocalizer(const std::filesystem::path& lang_root_directory) noexcept;
    void switch_language(LanguageCode lang);
    template <typename ...Args>
    std::string get_localized_text(std::string text_id, Args ... args) const;
    std::string get_localized_text(std::string_view text_id) const;
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
