#include "../../include/observers/StationsObserver.hpp"


void StationsObserver::on_notify(const std::any& any, Context context, events::Event e)
{
    switch (e)
    {
    case events::Event::AddStation:
    {
        auto station = std::any_cast<Station>(any);
        context.stations_manager.add_station(station);
    }
    break;
    case events::Event::DeleteStation:
    {
        auto station = std::any_cast<Station>(any);
        context.stations_manager.delete_station(station);
    }
    break;
    }
   
}
