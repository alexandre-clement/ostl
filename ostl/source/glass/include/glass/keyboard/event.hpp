#pragma once

#include <functional>

#include "action.hpp"
#include "key.hpp"

namespace glass::keyboard
{
    struct event
    {
        key keycode;
        action key_action;
    };

    using callback = std::function<void(event)>;
}  // namespace glass::keyboard