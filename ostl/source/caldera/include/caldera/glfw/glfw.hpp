#pragma once

#include <string>
#include <functional>

#include <GLFW/glfw3.h>

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

        protected:
        [[nodiscard]] std::vector<const char*> required_extensions() const;

        template<class surface, class instance>
        std::function<surface(instance)> meta_surface_maker()
        {
            return [&](instance p_instance) -> surface {
                surface s;
                glfwCreateWindowSurface(p_instance, m_window, nullptr, &s);
                return s;
            };
        }

    private:
        using glfw_pointer = GLFWwindow*;
        glfw_pointer m_window;
        std::string m_title;

        static glfw& controller(glfw_pointer);

        static void key_callback(glfw_pointer, int, int, int, int);
    };
}  // namespace caldera