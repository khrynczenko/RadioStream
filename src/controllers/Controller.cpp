#include "../../include/controllers/Controller.hpp"

Controller::Controller(StatesManager& manager, State::Context context)
    : manager_(manager)
    , context_(context)
    
{
}
