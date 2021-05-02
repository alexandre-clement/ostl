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

        glfwGetWindowPos(m_window, &m_position.x, &m_position.y);
        glfwGetWindowSize(m_window, &m_size.x, &m_size.y);
        glfwGetFramebufferSize(m_window, &m_framebuffer.x, &m_framebuffer.y);
        m_refresh_rate = mode->refreshRate;

        glfwSetWindowUserPointer(m_window, this);
        glfwSetKeyCallback(m_window, key_callback);
        glfwSetWindowPosCallback(m_window, window_pos_callback);
        glfwSetWindowSizeCallback(m_window, window_size_callback);
        glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    }

    [[nodiscard]] bool glfw::is_open() const { return !glfwWindowShouldClose(m_window); }

    void glfw::close() { glfwSetWindowShouldClose(m_window, GLFW_TRUE); }

    const abacus::ivec2& glfw::position() const { return m_position; }

    const abacus::ivec2& glfw::size() const { return m_size; }

    const abacus::ivec2& glfw::framebuffer() const { return m_framebuffer; }

    const int& glfw::refresh_rate() const { return m_refresh_rate; }

    void glfw::minimize() { glfwIconifyWindow(m_window); }

    void glfw::maximize() { glfwMaximizeWindow(m_window); }

    void glfw::fullscreen()
    {
        GLFWmonitor* monitor = current_monitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        log.info("selected monitor '{}' : {}x{} at {} Hz", glfwGetMonitorName(monitor), mode->width, mode->height, mode->refreshRate);

        if (!is_fullscreen())
        {
            m_pre_fullscreen_position = m_position;
            m_pre_fullscreen_size = m_size;
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
                            std::min(m_position.x + m_size.x, monitor_position.x + mode->width)
                              - std::max(m_position.x, monitor_position.x))
                          * std::max(0,
                            std::min(m_position.y + m_size.y, monitor_position.y + mode->height)
                              - std::max(m_position.y, monitor_position.y));

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
        self.m_position.x = xpos;
        self.m_position.y = ypos;

        GLFWmonitor* monitor = self.current_monitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        self.m_refresh_rate = mode->refreshRate;
    }

    void glfw::window_size_callback(GLFWwindow* p_window, int p_width, int p_height)
    {
        glfw& self = controller(p_window);
        self.m_size.x = p_width;
        self.m_size.y = p_height;
    }

    void glfw::framebuffer_size_callback(GLFWwindow* p_window, int p_width, int p_height)
    {
        glfw& self = controller(p_window);
        self.m_framebuffer.x = p_width;
        self.m_framebuffer.y = p_height;
    }
}  // namespace caldera