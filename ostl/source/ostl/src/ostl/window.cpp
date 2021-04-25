#include "ostl/window.hpp"

#include <abacus/abacus.hpp>
#include <caldera/caldera.hpp>

namespace ostl
{
    window::window() : window("untitled window") {}

    window::window(std::string p_title)
        : m_glass(std::make_unique<caldera::caldera>(p_title))
        , m_start(std::chrono::steady_clock::now())
    {
        m_shader.add_uniform(&m_glass->size());
        m_shader.add_uniform(&m_elapsed);

        m_glass->draw(m_shader);
    }

    void window::poll_events() { m_glass->poll_events(); }

    bool window::is_open() const noexcept { return m_glass->is_open(); }

    void window::close() { m_glass->close(); }

    void window::minimize() { m_glass->minimize(); }
    void window::maximize() { m_glass->maximize(); }
    void window::fullscreen() { m_glass->fullscreen(); }
    void window::restore() { m_glass->restore(); }

    bool window::is_fullscreen() const { return m_glass->is_fullscreen(); }

    void window::render()
    {
        auto now = std::chrono::high_resolution_clock::now();
        m_elapsed = std::chrono::duration<float, std::chrono::seconds::period>(now - m_start).count();
        m_glass->render();
    }

    void window::set_key_callback(ostl::keyboard::callback kc) { m_glass->event_handler.use_listener(kc); }
}  // namespace ostl