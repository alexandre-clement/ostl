#include "caldera/glfw/glfw.hpp"

#include "caldera/glfw/glfw_utils.hpp"

namespace caldera
{
    glfw::glfw(std::string p_title) : m_title(std::move(p_title))
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        log.info("selected monitor '{}' : {}x{} at {} Hz", glfwGetMonitorName(monitor), mode->width, mode->height, mode->refreshRate);
        m_window = glfwCreateWindow(mode->width, mode->height, m_title.c_str(), nullptr, nullptr);

        glfwGetWindowPos(m_window, &position.x, &position.y);
        glfwGetWindowSize(m_window, &size.x, &size.y);
        glfwGetFramebufferSize(m_window, &framebuffer.x, &framebuffer.y);

        glfwSetWindowUserPointer(m_window, this);
        glfwSetKeyCallback(m_window, key_callback);
        glfwSetWindowPosCallback(m_window, window_pos_callback);
        glfwSetWindowSizeCallback(m_window, window_size_callback);
        glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    }

    [[nodiscard]] bool glfw::is_open() const { return !glfwWindowShouldClose(m_window); }

    void glfw::close() { glfwSetWindowShouldClose(m_window, GLFW_TRUE); }

    void glfw::minimize() { glfwIconifyWindow(m_window); }

    void glfw::maximize() { glfwMaximizeWindow(m_window); }

    void glfw::fullscreen()
    {
        GLFWmonitor* monitor = current_monitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        log.info("selected monitor '{}' : {}x{} at {} Hz", glfwGetMonitorName(monitor), mode->width, mode->height, mode->refreshRate);

        if (!is_fullscreen())
        {
            m_pre_fullscreen_position = position;
            m_pre_fullscreen_size = size;
            glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        else
        {
            glfwSetWindowMonitor(m_window,
              NULL,
              m_pre_fullscreen_position.x,
              m_pre_fullscreen_position.y,
              m_pre_fullscreen_size.x,
              m_pre_fullscreen_size.y,
              mode->refreshRate);
        }
    }

    void glfw::restore() { glfwRestoreWindow(m_window); }

    bool glfw::is_fullscreen() const { return glfwGetWindowMonitor(m_window) != NULL; }

    void glfw::poll_events() { glfwPollEvents(); }

    void glfw::wait_events() { glfwWaitEvents(); }

    glfw::glfw_pointer glfw::handle() { return m_window; }

    glfw::glfw_pointer glfw::handle() const { return m_window; }

    GLFWmonitor* glfw::current_monitor() const
    {
        if (is_fullscreen())
        {
            return glfwGetWindowMonitor(m_window);
        }

        int number_of_monitors;
        int best_overlap = 0;
        GLFWmonitor* best_monitor = NULL;
        GLFWmonitor** monitors = glfwGetMonitors(&number_of_monitors);

        for (int i = 0; i < number_of_monitors; ++i)
        {
            const GLFWvidmode* mode = glfwGetVideoMode(monitors[i]);
            abacus::ivec2 monitor_position;
            glfwGetMonitorPos(monitors[i], &monitor_position.x, &monitor_position.y);
            int overlap = std::max(0,
                            std::min(position.x + size.x, monitor_position.x + mode->width)
                              - std::max(position.x, monitor_position.x))
                          * std::max(0,
                            std::min(position.y + size.y, monitor_position.y + mode->height)
                              - std::max(position.y, monitor_position.y));

            if (overlap > best_overlap)
            {
                best_overlap = overlap;
                best_monitor = monitors[i];
            }
        }

        return best_monitor;
    }

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

    void glfw::window_pos_callback(GLFWwindow* p_window, int xpos, int ypos)
    {
        glfw& self = controller(p_window);
        self.position.x = xpos;
        self.position.y = ypos;
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