#include "../include/StatusBar.hpp"
#include <string>

StatusBar::StatusBar(nana::window window)
    : nana::label(window)
{
}

void StatusBar::change_color(const nana::color& color)
{
    bgcolor(color);
}

void StatusBar::change_text(std::string text)
{
    using namespace std::string_literals;
    caption(" "s + std::move(text));
}
