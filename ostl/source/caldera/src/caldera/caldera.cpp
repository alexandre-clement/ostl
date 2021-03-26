#include "caldera/caldera.hpp"

#include "caldera/glfw/glfw_utils.hpp"

namespace caldera
{
    caldera::caldera(std::string p_title) : m_title(p_title)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        m_window = glfwCreateWindow(mode->width, mode->height, m_title.c_str(), nullptr, nullptr);

        glfwSetWindowUserPointer(m_window, this);
        glfwSetKeyCallback(m_window, key_callback);
    }

    [[nodiscard]] bool caldera::is_open() const { return !glfwWindowShouldClose(m_window); }

    void caldera::close() { glfwSetWindowShouldClose(m_window, GLFW_TRUE); }

    void caldera::minimize() { glfwIconifyWindow(m_window); }

    void caldera::maximize() { glfwMaximizeWindow(m_window); }

    void caldera::fullscreen()
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }

    void caldera::poll_events() { glfwPollEvents(); }

    void caldera::draw() {}

    caldera& caldera::controller(glfw_pointer p_window)
    {
        return *reinterpret_cast<caldera*>(glfwGetWindowUserPointer(p_window));
    }

    void caldera::key_callback(glfw_pointer p_window, int key, int scancode, int action, int mods)
    {
        caldera& self = controller(p_window);
        glass::keyboard::key k = glfw_key_convert(key);

        switch (action)
        {
            case GLFW_PRESS:
                self.press(k);
                break;
        }
    }
}  // namespace caldera