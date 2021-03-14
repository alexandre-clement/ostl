#pragma once

#include "keyboard.hpp"

namespace glass::event
{
    class handler
    {
    public:
        void use_listener(key_callback kc);
    };
}  // namespace glass::event