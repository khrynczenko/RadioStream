#ifndef STATUSBAR_HPP
#define STATUSBAR_HPP

#pragma warning (push, 0)
#include <nana/gui/widgets/label.hpp>
#pragma warning (pop)

class StatusBar : public nana::label
{
public:
    class Color
    {
    public:
        inline const static nana::color FINISHED{5,255,51};
        inline const static nana::color PROCESSING{255,128,0};
        inline const static nana::color ERRORED{153,0,0};
    };
    explicit StatusBar(nana::window window);
    void change_color(const nana::color& color);
    void change_text(std::string text);
};

#endif