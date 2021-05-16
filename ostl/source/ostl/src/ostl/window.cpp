#include "ostl/window.hpp"

#include <abacus/abacus.hpp>
#include <caldera/caldera.hpp>

namespace ostl
{
    window::window() : window("untitled window") {}

    window::window(std::string p_title)
        : m_glass(std::make_unique<caldera::caldera>(p_title))
        , m_start(m_stopwatch.now())
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
        if (!vsync_enabled()) [[likely]]
        {
            auto now = std::chrono::high_resolution_clock::now();
            m_elapsed = std::chrono::duration<float, std::chrono::seconds::period>(now - m_start).count();
            m_glass->render();
        }
        else [[unlikely]]
        {
            m_stopwatch.wait_vertical_synchronisation(m_framerate);

            auto now = std::chrono::high_resolution_clock::now();
            m_elapsed = std::chrono::duration<float, std::chrono::seconds::period>(now - m_start).count();

            m_stopwatch.start_rendering();
            m_glass->render();
            m_stopwatch.finished_rendering();
        }
    }

    const int& window::monitor_refresh_rate() const { return m_glass->refresh_rate(); }

    void window::enable_vsync() { set_framerate(m_glass->refresh_rate()); }
    void window::disable_vsync() { unset_framerate(); }

    void window::toggle_vsync() { vsync_enabled() ? disable_vsync() : enable_vsync(); }

    bool window::vsync_enabled() const { return m_framerate > 0; }

    void window::set_framerate(const int p_framerate) { m_framerate = p_framerate; }
    void window::unset_framerate() { m_framerate = 0; }

    int window::framerate() const { return m_framerate; }

    void window::set_key_callback(ostl::keyboard::callback kc) { m_glass->event_handler.use_listener(kc); }
}  // namespace ostl