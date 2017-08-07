#ifndef STATUSBAR_HPP
#define STATUSBAR_HPP

#include <nana/gui/widgets/label.hpp>

class StatusBar : public nana::label
{
public:
    explicit StatusBar(nana::window window);
    void change_color(const nana::color& color);
    void change_text(std::string text);
};

#endif