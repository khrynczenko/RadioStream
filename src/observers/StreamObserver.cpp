#include "../../include/observers/StreamObserver.hpp"
#include "../../include/Constants.hpp"
#include "../../include/Utilities.hpp"

void StreamObserver::on_notify(const std::any& any, Context context, events::Event e)
{
	using namespace constants;
	switch(e)
	{
	case events::Event::StreamPause:
    {
        context.stream_manager.pause();
    }
    break;

	case events::Event::StreamPlay:
	{
        context.stream_manager.play();
	}
	break;

	case events::Event::StreamVolumeChanged:
	{
        context.stream_manager.set_current_volume(volume_int_to_float(std::any_cast<unsigned>(any)));
	}
	break;

	case events::Event::StreamSetNew:
	{
        const auto station_name = std::any_cast<std::string>(any);
        const auto station_ip = context.stations_manager.get_station_ip(station_name);
        context.stream_manager.set_stream(station_ip);
        context.stream_manager.play();
	}
	break;

	case events::Event::StreamMute:
    {
        context.stream_manager.set_current_volume(0.f);
    }
	break;

	}
}
