#include <cstdlib>

#include <ostl/ostl.hpp>

int main()
{
    detail::set_level(detail::level::level_enum::trace);
    ostl::window window("simple window");
    // window.enable_vsync();
    window.set_framerate(window.monitor_refresh_rate() * 2);

    window.set_key_callback([&](ostl::keyboard::event key) {
        if (key.keycode == ostl::keyboard::key::escape && key.key_action == ostl::keyboard::action::press)
        {
            window.close();
        }
        if (key.keycode == ostl::keyboard::key::f11 && key.key_action == ostl::keyboard::action::press)
        {
            window.fullscreen();
        }
        if (key.keycode == ostl::keyboard::key::v && key.key_action == ostl::keyboard::action::press)
        {
            window.toggle_vsync();
        }
    });

    ostl::sphere sphere;

    while (window.is_open())
    {
        window.poll_events();
        window.draw(sphere);
        window.render();
    }

    return EXIT_SUCCESS;
}
