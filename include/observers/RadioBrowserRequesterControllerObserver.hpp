#ifndef RADIOBROWSERREQUESTERCONTROLLEROBSERVER_HPP
#define RADIOBROWSERREQUESTERCONTROLLEROBSERVER_HPP
#include "Observer.hpp"
#include "../controllers/RadioBrowserRequesterController.hpp"

class RadioBrowserRequesterControllerObserver : public Observer
{
public:
    explicit RadioBrowserRequesterControllerObserver(RadioBrowserRequesterController& controller) noexcept;
    void on_notify(const std::any& data, radiostream::Event e) override;
private:
    RadioBrowserRequesterController& controller_;
};

#endif