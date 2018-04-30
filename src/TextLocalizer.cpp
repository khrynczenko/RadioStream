#include "../include/TextLocalizer.hpp"
#include "../include/exceptions/LanguageFileNotFound.hpp"

using namespace std::string_literals;
const std::map<const LanguageCode, const LanguageNativeName, KeyComparator> LANGUAGES_CODES_AND_TRANSLATIONS =
{
    std::make_pair(LanguageCode("en"s), "English"s),
    std::make_pair(LanguageCode("pl"s), "Polski"s)
};

LanguagesPathsContainer::LanguagesPathsContainer() noexcept
    : languages_filpaths_()
{
    languages_filpaths_.insert({ LanguageCode("en"), std::experimental::filesystem::path("lang/en.po") });
    languages_filpaths_.insert({ LanguageCode("pl"), std::experimental::filesystem::path("lang/pl.po") });
}

std::experimental::filesystem::path LanguagesPathsContainer::get_path(LanguageCode lang)
{
    auto path = languages_filpaths_.at(lang);
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
	const auto path = languages_.get_path(lang).string();
	localizer_.load_utf8(path);
}

std::string TextLocalizer::get_localized_text(std::string text_id) const
{
	return localizer_.get(text_id);
}

bool KeyComparator::operator()(LanguageCode lhs, LanguageCode rhs) const noexcept
{
    return lhs.as_string() < rhs.as_string();
}
