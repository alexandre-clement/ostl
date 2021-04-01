#pragma once

#include <string>

#include "handler.hpp"
#include "keyboard/key.hpp"

namespace glass
{
    class base
    {
    public:
        base() = default;
        virtual ~base() = default;

        [[nodiscard]] virtual bool is_open() const = 0;

        virtual void close() = 0;

        virtual void minimize() = 0;
        virtual void maximize() = 0;
        virtual void fullscreen() = 0;

        virtual void poll_events() = 0;
        virtual void draw() = 0;

        virtual void render() = 0;

        void press(keyboard::key);

        handler event_handler;
    };
}  // namespace glass