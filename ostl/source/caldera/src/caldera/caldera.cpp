#include "caldera/caldera.hpp"

#include <chrono>

#include "caldera/glfw/glfw_utils.hpp"

namespace caldera
{
    std::tm localtime(const std::time_t& time)
    {
        std::tm tm_snapshot;
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
        localtime_s(&tm_snapshot, &time);
#else
        localtime_r(&time, &tm_snapshot);  // POSIX
#endif
        return tm_snapshot;
    }

    std::uint32_t default_version()
    {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        auto local = localtime(in_time_t);
        return local.tm_year * 10000u + local.tm_mon * 100u + local.tm_mday;
    }

    caldera::caldera(std::string p_title) : caldera(std::move(p_title), default_version()) {}

    caldera::caldera(std::string p_title, std::uint32_t p_version)
        : glfw(p_title)
        , m_renderer({p_title, p_version, debug::none, required_extensions(), create_surface_maker(), create_idle(), framebuffer})
    {
    }

    void caldera::draw() {}

    void caldera::render()
    {
        m_renderer.add_uniform(&size);
        m_renderer.render();
    }

    std::vector<const char*> caldera::required_extensions() const
    {
        std::vector<const char*> required_extensions;
        std::uint32_t count = 0;
        const char** glfw_required_extensions = glfwGetRequiredInstanceExtensions(&count);
        for (const char** index = glfw_required_extensions; index < glfw_required_extensions + count; ++index)
        {
            required_extensions.push_back(*index);
        }
        return required_extensions;
    }

    surface_maker caldera::create_surface_maker()
    {
        return [&](vk::Instance& p_instance) -> vk::SurfaceKHR {
            VkSurfaceKHR surface;
            glfwCreateWindowSurface(p_instance, handle(), nullptr, &surface);
            return std::move(surface);
        };
    }

    idle caldera::create_idle()
    {
        return [&]() { wait_events(); };
    }
}  // namespace caldera