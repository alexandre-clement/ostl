#pragma once

#include <chrono>
#include <memory>
#include <string>

#include <glass/glass.hpp>

#include "drawer.hpp"
#include "event.hpp"
#include "stopwatch.hpp"
#include "texture.hpp"
#include "texture/no_texture.hpp"

namespace ostl
{
    class window
    {
    public:
        window();
        explicit window(std::string);
        window(const window&) = delete;
        window(window&&) noexcept = default;
        window& operator=(const window&) = delete;
        window& operator=(window&&) noexcept = default;
        ~window() = default;

        [[nodiscard]] bool is_open() const noexcept;

        void close();

        void minimize();
        void maximize();
        void fullscreen();
        void restore();

        [[nodiscard]] bool is_fullscreen() const;

        void poll_events();

        template<drawable object>
        void draw(object);

        template<drawable object>
        void draw(object, texture);

        void render();

        [[nodiscard]] const int& monitor_refresh_rate() const;
        void enable_vsync();
        void disable_vsync();
        void toggle_vsync();
        [[nodiscard]] inline bool vsync_enabled() const;
        void set_framerate(const int);
        void unset_framerate();
        [[nodiscard]] int framerate() const;

        void set_key_callback(ostl::keyboard::callback kc);

    private:
        std::unique_ptr<glass::base> m_glass;
        glass::shader m_shader;
        std::chrono::steady_clock::time_point m_start;
        float m_elapsed = 0.f;
        int m_framerate = 0;
        stopwatch m_stopwatch;
    };

    template<drawable object>
    void window::draw(object obj)
    {
        this->draw(obj, no_texture());
    }

    template<drawable object>
    void window::draw(object obj, texture text)
    {
        drawer<object>::draw(obj, text);
    }
}  // namespace ostl