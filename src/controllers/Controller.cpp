#include "../../include/controllers/Controller.hpp"

Controller::Controller(StatesManager& manager, State::Context context) noexcept
    : Observer()
    , manager_(manager)
    , context_(context)
{
}
