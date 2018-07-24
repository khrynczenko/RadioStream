#include "../../include/controllers/StatusBarController.hpp"
#include "../../include/Constants.hpp"
#include <iostream>
#include <map>

using namespace std::string_literals;
const std::map<BassErrorCode, BassErrorMessage> ERROR_CODES_AND_MESSAGES =
{
    {BASS_ERROR_INIT,	"BASS_Init has not been successfully called."s},
    {BASS_ERROR_NOTAVAIL,	"Only decoding channels(BASS_STREAM_DECODE) are allowed when using the 'no sound' device.The BASS_STREAM_AUTOFREE flag is also unavailable to decoding channels."s},
    {BASS_ERROR_NONET,	"No internet connection could be opened.Can be caused by a bad proxy setting."s},
    {BASS_ERROR_ILLPARAM,	"url is not a valid URL."s},
    {BASS_ERROR_SSL,	"SSL / HTTPS support is not available."s},
    {BASS_ERROR_TIMEOUT,	"The server did not respond to the request within the timeout period, as set with the BASS_CONFIG_NET_TIMEOUT config option."s},
    {BASS_ERROR_FILEOPEN,	"The file could not be opened."s},
    {BASS_ERROR_FILEFORM,	"The file's format is not recognised/supported."s},
    {BASS_ERROR_CODEC,	"The file uses a codec that is not available / supported.This can apply to WAV and AIFF files, and also MP3 files when using the 'MP3-free' BASS version."s},
    {BASS_ERROR_FORMAT,	"The sample format is not supported by the device / drivers.If the stream is more than stereo or the BASS_SAMPLE_FLOAT flag is used, it could be that they are not supported."s},
    {BASS_ERROR_SPEAKER,	"The specified SPEAKER flags are invalid.The device / drivers do not support them, they are attempting to assign a stereo stream to a mono speaker or 3D functionality is enabled."s},
    {BASS_ERROR_MEM,	"There is insufficient memory."s},
    {BASS_ERROR_NO3D,	"Could not initialize 3D support."s},
    {BASS_ERROR_UNKNOWN,	"Some other mystery problem!"s},
};

StatusBarController::StatusBarController(StatesManager& manager, State::Context context, StatusBar& statusbar) noexcept
    : Controller(manager, context)
    , statusbar_(statusbar)
{
}

void StatusBarController::on_notify(const radiostream::Event e, const std::any &data)
{
    switch (e)
    {
    case radiostream::Event::StationPaused:
    {
        context_.status_.change_text(context_.localizer_.get_localized_text("Stream paused"));
        context_.status_.change_color(StatusBar::Color::FINISHED);
    }
    break;

    case radiostream::Event::NewStationLoading:
    {
        context_.status_.change_text(context_.localizer_.get_localized_text("Loading station..."));
        context_.status_.change_color(StatusBar::Color::PROCESSING);
    }
    break;

    case radiostream::Event::NewStationSet:
    {
        context_.status_.change_text(context_.localizer_.get_localized_text("Station ready"));
        context_.status_.change_color(StatusBar::Color::FINISHED);
    }
    break;

    case radiostream::Event::StationStartedPlaying:
    {
        context_.status_.change_text(context_.localizer_.get_localized_text("Station playing"));
        context_.status_.change_color(StatusBar::Color::FINISHED);
    }
    break;

    case radiostream::Event::StreamLoadingError:
    {
        auto error_code = std::any_cast<int>(data);

        const auto error_message = [error_code]()
        {
            try
            {
                return ERROR_CODES_AND_MESSAGES.at(error_code);
            }
            catch (const std::out_of_range& e)
            {
                return std::string("Unknown message");
            }
        }();
        context_.status_.change_text(context_.localizer_.get_localized_text("Could not load station: " +
            context_.localizer_.get_localized_text(error_message)));
        context_.status_.change_color(StatusBar::Color::FINISHED);
    }
    break;

    case radiostream::Event::StationMuted:
    {
        context_.status_.change_text(context_.localizer_.get_localized_text("Stream muted"));
        context_.status_.change_color(StatusBar::Color::PROCESSING);
    }
    break;

    case radiostream::Event::StationUnmuted:
    {
        context_.status_.change_text(context_.localizer_.get_localized_text("Station unmuted"));
        context_.status_.change_color(StatusBar::Color::FINISHED);
    }
    break;
    }
}
