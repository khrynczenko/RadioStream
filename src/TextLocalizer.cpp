#include "../include/TextLocalizer.hpp"
#include "../include/exceptions/LanguageFileNotFound.hpp"
LanguagesPathsContainer::LanguagesPathsContainer() noexcept
	: languages_()
{
	languages_.at(static_cast<std::size_t>(Language::EN)) = "lang/en.po";
	languages_.at(static_cast<std::size_t>(Language::PL)) = "lang/pl.po";
}

std::experimental::filesystem::path LanguagesPathsContainer::get_path(Language lang)
{
	auto path = languages_.at(static_cast<std::size_t>(lang));
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

void TextLocalizer::switch_language(Language lang)
{
	const auto path = languages_.get_path(lang).string();
	localizer_.load_utf8(path);
}

std::string TextLocalizer::get_localized_text(std::string text_id) const
{
	return localizer_.get(text_id);
}