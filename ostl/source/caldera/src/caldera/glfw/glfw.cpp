#include "caldera/glfw/glfw.hpp"

#include "caldera/glfw/glfw_utils.hpp"

namespace caldera
{
    glfw::glfw(std::string p_title) : m_title(std::move(p_title))
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        m_window = glfwCreateWindow(mode->width, mode->height, m_title.c_str(), nullptr, nullptr);

        glfwSetWindowUserPointer(m_window, this);
        glfwSetKeyCallback(m_window, key_callback);
    }

    [[nodiscard]] bool glfw::is_open() const { return !glfwWindowShouldClose(m_window); }

    void glfw::close() { glfwSetWindowShouldClose(m_window, GLFW_TRUE); }

    void glfw::minimize() { glfwIconifyWindow(m_window); }

    void glfw::maximize() { glfwMaximizeWindow(m_window); }

    void glfw::fullscreen()
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }

    void glfw::poll_events() { glfwPollEvents(); }

    [[nodiscard]] glfw::glfw_pointer glfw::handle() { return m_window; }
    [[nodiscard]] glfw::glfw_pointer glfw::handle() const { return m_window; }

    glfw& glfw::controller(glfw_pointer p_window)
    {
        return *reinterpret_cast<glfw*>(glfwGetWindowUserPointer(p_window));
    }

    void glfw::key_callback(glfw_pointer p_window, int key, int scancode, int action, int mods)
    {
        glfw& self = controller(p_window);
        glass::keyboard::key k = glfw_key_convert(key);

        switch (action)
        {
            case GLFW_PRESS:
                self.press(k);
                break;
        }
    }
}  // namespace caldera