#include "glass/glass.hpp"

namespace glass
{
    void base::press(keyboard::key k)
    {
        event_handler.trigger(keyboard::event{.keycode = k, .key_action = keyboard::action::press});
    }
}  // namespace glass