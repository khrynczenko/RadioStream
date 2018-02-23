#ifndef STATUSBAR_HPP
#define STATUSBAR_HPP

#include <nana/gui/widgets/label.hpp>

class StatusBar : public nana::label
{
public:
    class Color
    {
    public:
        inline static nana::color FINISHED{5,255,51};
        inline static nana::color PROCESSING{255,128,0};
        inline static nana::color ERRORED{153,0,0};
    };
    explicit StatusBar(nana::window window);
    void change_color(const nana::color& color);
    void change_text(std::string text);
};

#endif