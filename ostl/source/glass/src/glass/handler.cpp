#include "glass/handler.hpp"

namespace glass
{
    void handler::trigger(keyboard::event e) { keyboard_callback(e); }

    void handler::use_listener(keyboard::callback kc) { keyboard_callback = kc; }
}  // namespace glass