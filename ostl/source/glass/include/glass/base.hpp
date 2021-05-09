#pragma once

#include <string>

#include <abacus/abacus.hpp>

#include "handler.hpp"
#include "keyboard/key.hpp"
#include "shader.hpp"

namespace glass
{
    class base
    {
    public:
        base() = default;
        virtual ~base() = default;

        [[nodiscard]] virtual bool is_open() const = 0;

        virtual void close() = 0;

        [[nodiscard]] virtual const abacus::ivec2& position() const = 0;
        [[nodiscard]] virtual const abacus::ivec2& size() const = 0;
        [[nodiscard]] virtual const abacus::ivec2& framebuffer() const = 0;
        [[nodiscard]] virtual const int& refresh_rate() const = 0;

        virtual void minimize() = 0;
        virtual void maximize() = 0;
        virtual void fullscreen() = 0;
        virtual void restore() = 0;

        [[nodiscard]] virtual bool is_fullscreen() const = 0;

        virtual void poll_events() = 0;
        virtual void draw(const shader&) = 0;

        virtual void render() = 0;

        void press(keyboard::key);

        handler event_handler;
    };
}  // namespace glass