#pragma once

#include <string>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glass/glass.hpp>

#include "glfw/glfw_shell.hpp"
#include "renderer/renderer.hpp"

namespace caldera
{
    class caldera : public glass::base
    {
    public:
        caldera(std::string);
        virtual ~caldera() = default;

        [[nodiscard]] bool is_open() const override;

        void close() override;

        void minimize() override;
        void maximize() override;
        void fullscreen() override;

        void poll_events() override;

        void draw() override;

    private:
        using glfw_pointer = GLFWwindow*;
        glfw_pointer m_window;
        std::string m_title;
        renderer m_renderer;

        static caldera& controller(glfw_pointer);

        static void key_callback(glfw_pointer, int, int, int, int);
    };
}  // namespace caldera