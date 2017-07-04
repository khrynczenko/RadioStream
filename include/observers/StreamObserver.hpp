#ifndef STREAMOBSERVER_HPP
#define STREAMOBSERVER_HPP


#include "Observer.hpp"
#include <nana/gui/widgets/slider.hpp>
#include <nana/gui/widgets/button.hpp>

class StreamObserver :
    public Observer
{
public:
    StreamObserver(nana::slider& volume_slider, nana::button& mute_button);
    void on_notify(const nana::widget& caller, Context context, events::Event e) override;
private:
    nana::slider& volume_slider_;
    nana::button& mute_button_;
};

#endif
