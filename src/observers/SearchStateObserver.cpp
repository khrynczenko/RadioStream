#include "../../include/observers/SearchStateObserver.hpp"
#include "../../include/states/SearchState.hpp"

SearchStateObserver::SearchStateObserver(SearchState& state) noexcept
    : state_(state) 
{
}

void SearchStateObserver::on_notify(const std::any& data, radiostream::Event e)
{
    switch(e)
    {
        
    }
}
