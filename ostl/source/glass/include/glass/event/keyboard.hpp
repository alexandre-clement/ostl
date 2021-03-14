#pragma once

#include <functional>

#include "key.hpp"

namespace glass::event
{
    struct key_event
    {
        key keycode;
        action action;
    };

    using key_callback = std::function<void(key_event)>;
}  // namespace glass::event