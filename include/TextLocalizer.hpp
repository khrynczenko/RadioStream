#ifndef TEXTLOCALIZER_HPP
#define TEXTLOCALIZER_HPP

#include <nana/internationalization.hpp>
#include <array>
#include <experimental/filesystem>

enum class Language
{
    EN,
    PL,
    LanguagesCount
};

class LanguagesPathsContainer
{
public:
    LanguagesPathsContainer() noexcept;
    std::experimental::filesystem::path get_path(Language lang);

private:
    std::array<std::experimental::filesystem::path, static_cast<size_t>(Language::LanguagesCount)> languages_;
};

class TextLocalizer
{
public:
    TextLocalizer() noexcept;
    void switch_language(Language lang);
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
