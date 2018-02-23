#ifndef STREAMMANAGEROBSERVER_HPP
#define STREAMMANAGEROBSERVER_HPP
#include "Observer.hpp"
#include "../controllers/StreamManagerController.hpp"

class StreamManagerObserver : public Observer
{
public:
    StreamManagerObserver(StreamManagerController& controller);
    void on_notify(const std::any& data, events::Event e) override;
private:
    StreamManagerController& controller_;
    
};

#endif
