#include "../../include/observers/StationsDatabaseObserver.hpp"
#include "../../include/StationsDatabase.hpp"
#include "../../include/Station.hpp"

void StationsDatabaseObserver::on_notify(const std::any& any, Context context, events::Event e)
{
    switch (e)
    {
    case events::Event::AddStation:
    {
        const auto station = std::any_cast<Station>(any);

        context.stations_database.add_station(station, station.table_);
    }
    break;

    case events::Event::DeleteStation:
    {
        const auto station = std::any_cast<Station>(any);
        context.stations_database.remove_station(station, station.table_);
    }
    break;
    }
   
}
