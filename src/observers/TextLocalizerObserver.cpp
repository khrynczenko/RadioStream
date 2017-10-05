#include "../../include/observers/TextLocalizerObserver.hpp"

void TextLocalizerObserver::on_notify(const std::any& any, Context context, events::Event e)
{
	switch(e)
	{
	case events::Event::ChangeLanguage:
	{
		context.localizer.switch_language(std::any_cast<Language>(any));
	}
	}
}
