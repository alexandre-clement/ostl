#pragma once

#include <functional>
#include <string>

#include <GLFW/glfw3.h>

#include <abacus/abacus.hpp>
#include <detail/detail.hpp>
#include <glass/glass.hpp>

#include "glfw_shell.hpp"

namespace caldera
{
    class glfw
        : public glass::base
        , private detail::loggable<glfw>
    {
    public:
        glfw(std::string);
        virtual ~glfw() = default;

        [[nodiscard]] bool is_open() const override;

        void close() override;

        [[nodiscard]] const abacus::ivec2& position() const override;
        [[nodiscard]] const abacus::ivec2& size() const override;
        [[nodiscard]] const abacus::ivec2& framebuffer() const override;

        void minimize() override;
        void maximize() override;
        void fullscreen() override;
        void restore() override;

        [[nodiscard]] bool is_fullscreen() const override;

        void poll_events() override;
        void wait_events();

        using glfw_pointer = GLFWwindow*;
        [[nodiscard]] glfw_pointer handle();
        [[nodiscard]] glfw_pointer handle() const;

    private:
        [[nodiscard]] GLFWmonitor* current_monitor() const;

        glfw_pointer m_window;
        std::string m_title;

        abacus::ivec2 m_position;
        abacus::ivec2 m_size;
        abacus::ivec2 m_framebuffer;

        abacus::ivec2 m_pre_fullscreen_position;
        abacus::ivec2 m_pre_fullscreen_size;

        static glfw& controller(glfw_pointer);

        static void key_callback(glfw_pointer, int, int, int, int);
        static void window_pos_callback(GLFWwindow*, int, int);
        static void window_size_callback(GLFWwindow*, int, int);
        static void framebuffer_size_callback(GLFWwindow*, int, int);
    };
}  // namespace caldera