#include "../../include/states/State.hpp"
#include "../../include/states/StatesManager.hpp"
#include "../../include/StationPlayer.hpp"
#include "../../include/StationsDatabase.hpp"
#include "../../include/Config.hpp"
#include "../../include/RadioBrowserRequester.hpp"
#pragma warning(push, 0)
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/menubar.hpp>
#pragma warning(pop)

State::Context::Context(nana::form& window, nana::menubar& menubar,
                        StationPlayer& station_player,
                        StationsDatabase& stations_database, StatusBar& status,
                        TextLocalizer& localizer, Config& config,
                        RadioBrowserRequester& requester) noexcept
    : window_(window),
      menubar_(menubar),
      station_player_(station_player),
      stations_database_(stations_database),
      status_(status),
      localizer_(localizer),
      config_(config),
      requester_(requester) {}

State::State(StatesManager& state_manager, Context& context)
    : context_(context), manager_(state_manager) {}

void State::switch_state(States::ID id) const { manager_.switch_state(id); }
