#pragma once

#include <functional>
#include <string>

#include <GLFW/glfw3.h>

#include <abacus/abacus.hpp>
#include <glass/glass.hpp>

#include "glfw_shell.hpp"

namespace caldera
{
    class glfw : public glass::base
    {
    public:
        glfw(std::string);
        virtual ~glfw() = default;

        [[nodiscard]] bool is_open() const override;

        void close() override;

        void minimize() override;
        void maximize() override;
        void fullscreen() override;

        void poll_events() override;

        using glfw_pointer = GLFWwindow*;
        [[nodiscard]] glfw_pointer handle();
        [[nodiscard]] glfw_pointer handle() const;

        abacus::matrix<int, 1, 2> size;
        abacus::matrix<int, 1, 2> framebuffer;

    private:
        glfw_pointer m_window;
        std::string m_title;

        static glfw& controller(glfw_pointer);

        static void key_callback(glfw_pointer, int, int, int, int);
        static void window_size_callback(GLFWwindow*, int, int);
        static void framebuffer_size_callback(GLFWwindow*, int, int);
    };
}  // namespace caldera