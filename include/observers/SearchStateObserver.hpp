#ifndef SEARCHSTATEOBSERVER_HPP
#define SEARCHSTATEOBSERVER_HPP
#include "Observer.hpp"

class SearchState;

class SearchStateObserver : public Observer
{
public:
    explicit SearchStateObserver(SearchState& state) noexcept;
    void on_notify(const std::any& data, radiostream::Event e) override;
private:
    SearchState& state_;
};

#endif
