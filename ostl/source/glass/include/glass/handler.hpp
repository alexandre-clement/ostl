#pragma once

#include "keyboard/event.hpp"

namespace glass
{
    class handler
    {
    public:
        void trigger(keyboard::event);

        void use_listener(keyboard::callback kc);

    private:
        keyboard::callback keyboard_callback;
    };
}  // namespace glass