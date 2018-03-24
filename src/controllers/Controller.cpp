#include "../../include/controllers/Controller.hpp"

Controller::Controller(StatesManager& manager, State::Context context) noexcept
    : manager_(manager)
    , context_(context)
{
}
