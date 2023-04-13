#include "glass/handler.hpp"

namespace glass
{
    void handler::trigger(keyboard::event e) { m_keyboard_callback(e); }

    void handler::use_listener(keyboard::callback kc) { m_keyboard_callback = kc; }
}  // namespace glass