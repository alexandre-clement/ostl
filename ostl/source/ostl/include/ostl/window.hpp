#pragma once

#include <string>

#include "drawer.hpp"
#include "event.hpp"
#include "texture.hpp"
#include "texture/no_texture.hpp"
#include <glass/glass.hpp>

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

        void poll_events();

        template<drawable object>
        void draw(object);

        template<drawable object>
        void draw(object, texture);

        void render();

        void set_key_callback(ostl::event::key_callback kc);

    private:
        std::unique_ptr<glass::glass> m_glass;
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