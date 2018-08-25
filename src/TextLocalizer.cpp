#include "../include/TextLocalizer.hpp"
#include "../include/exceptions/LanguageFileNotFound.hpp"

LanguagesPathsContainer::LanguagesPathsContainer() noexcept
    : languages_filepaths()
{
    languages_filepaths.insert({ LanguageCode("en"), std::experimental::filesystem::path("lang/en.po") });
    languages_filepaths.insert({ LanguageCode("pl"), std::experimental::filesystem::path("lang/pl.po") });
}

std::experimental::filesystem::path LanguagesPathsContainer::get_path(LanguageCode lang)
{
    auto path = languages_filepaths.at(lang);
	if (!exists(path))
	{
        throw LanguageFileNotFound(path);
	}
	return path;
}

TextLocalizer::TextLocalizer() noexcept
	: localizer_()
	, languages_()
{
}

void TextLocalizer::switch_language(LanguageCode lang)
{
	const auto path = languages_.get_path(std::move(lang)).string();
	localizer_.load_utf8(path);
}

std::string TextLocalizer::get_localized_text(std::string text_id) const
{
	return localizer_.get(std::move(text_id));
}
