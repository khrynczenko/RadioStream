#include "../include/TextLocalizer.hpp"
#include "../include/exceptions/LanguageFileNotFound.hpp"

LanguagesPathsContainer::LanguagesPathsContainer(
    const std::filesystem::path& lang_root_directory) noexcept
    : languages_filepaths() {
    languages_filepaths.insert({LanguageCode("en"), lang_root_directory / "lang/en.po"});
    languages_filepaths.insert({LanguageCode("pl"), lang_root_directory / "lang/pl.po"});
}

std::filesystem::path LanguagesPathsContainer::get_path(LanguageCode lang) {
    auto path = languages_filepaths.at(lang);
    if (!exists(path)) {
        throw LanguageFileNotFound(path);
    }
    return path;
}

TextLocalizer::TextLocalizer(const std::filesystem::path& lang_root_directory) noexcept
    : localizer_(), languages_(lang_root_directory) {}

void TextLocalizer::switch_language(LanguageCode lang) {
    const auto path = languages_.get_path(std::move(lang)).string();
    localizer_.load_utf8(path);
}

std::string TextLocalizer::get_localized_text(std::string_view text_id) const {
    return localizer_.get(std::string(text_id));
}
