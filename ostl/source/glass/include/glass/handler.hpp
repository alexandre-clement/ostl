#pragma once

#include "keyboard/event.hpp"

namespace glass
{
    class handler
    {
    public:
        void use_listener(keyboard::callback kc);
    };
}  // namespace glass