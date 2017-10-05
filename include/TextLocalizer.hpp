#ifndef TEXTLOCALIZER_HPP
#define TEXTLOCALIZER_HPP

#include <nana/internationalization.hpp>
#include "Constants.hpp"
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
	LanguagesPathsContainer();
	std::experimental::filesystem::path get_path(Language lang);

private:
	std::array<std::experimental::filesystem::path, static_cast<std::size_t>(Language::LanguagesCount)> languages_;
};

class TextLocalizer
{
public:
	TextLocalizer();
	void switch_language(Language lang);
	template <typename ...Args>
	std::string get_localized_text(std::string text_id, Args... args);
	std::string get_localized_text(std::string text_id);
private:
	nana::internationalization localizer_;
	LanguagesPathsContainer languages_;
};


template <typename ... Args>
std::string TextLocalizer::get_localized_text(std::string text_id, Args... args)
{
	return localizer_(text_id, args...);
}

#endif
