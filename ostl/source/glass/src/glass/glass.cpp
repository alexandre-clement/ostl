#include "glass/glass.hpp"

namespace glass
{
    void glass::press(keyboard::key k)
    {
        event_handler.trigger(keyboard::event{.keycode = k, .key_action = keyboard::action::press});
    }
}  // namespace glass