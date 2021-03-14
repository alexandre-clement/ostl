#include <cstdlib>

#include <ostl/ostl.hpp>

int main()
{
    ostl::window window("simple window");

    window.set_key_callback([&](ostl::event::key_event key) {
        if (key.keycode == ostl::event::key::escape && key.action == ostl::event::action::press)
        {
            window.close();
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
