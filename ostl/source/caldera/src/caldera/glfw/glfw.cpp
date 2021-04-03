#include "caldera/glfw/glfw.hpp"

#include "caldera/glfw/glfw_utils.hpp"

namespace caldera
{
    glfw::glfw(std::string p_title) : m_title(std::move(p_title))
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        m_window = glfwCreateWindow(mode->width, mode->height, m_title.c_str(), nullptr, nullptr);

        glfwGetWindowSize(m_window, &size.x, &size.y);
        glfwGetFramebufferSize(m_window, &framebuffer.x, &framebuffer.y);

        glfwSetWindowUserPointer(m_window, this);
        glfwSetKeyCallback(m_window, key_callback);
        glfwSetWindowSizeCallback(m_window, window_size_callback);
        glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
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

    void glfw::key_callback(glfw_pointer p_window, int key, int, int action, int)
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

    void glfw::window_size_callback(GLFWwindow* p_window, int p_width, int p_height)
    {
        glfw& self = controller(p_window);
        self.size.x = p_width;
        self.size.y = p_height;
    }

    void glfw::framebuffer_size_callback(GLFWwindow* p_window, int p_width, int p_height)
    {
        glfw& self = controller(p_window);
        self.framebuffer.x = p_width;
        self.framebuffer.y = p_height;
    }
}  // namespace caldera