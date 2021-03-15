#include "ostl/window.hpp"

#include <abacus/abacus.hpp>
#include <caldera/caldera.hpp>

namespace ostl
{
    window::window() : window("untitled window") {}

    window::window(std::string p_title) : m_glass(std::make_unique<caldera::caldera>(p_title)) {}

    void window::poll_events() { m_glass->poll_events(); }

    bool window::is_open() const noexcept { return m_glass->is_open(); }

    void window::close() { m_glass->close(); }

    void window::minimize() { m_glass->minimize(); }
    void window::maximize() { m_glass->maximize(); }
    void window::fullscreen() { m_glass->fullscreen(); }

    void window::render() {}

    void window::set_key_callback(ostl::keyboard::callback kc) { m_glass->event_handler.use_listener(kc); }
}  // namespace ostl