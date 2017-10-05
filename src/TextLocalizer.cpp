#include "../include/TextLocalizer.hpp"

LanguagesPathsContainer::LanguagesPathsContainer()
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
		throw std::runtime_error("Language not found.");
	}
	return path;
}

TextLocalizer::TextLocalizer()
	: localizer_()
	, languages_()
{
}

void TextLocalizer::switch_language(Language lang)
{
	const auto path = languages_.get_path(lang).string();
	localizer_.load_utf8(path);
}

std::string TextLocalizer::get_localized_text(std::string str)
{
	return localizer_.get(str);
}