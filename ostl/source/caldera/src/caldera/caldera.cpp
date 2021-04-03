#include "caldera/caldera.hpp"

#include "caldera/glfw/glfw_utils.hpp"

namespace caldera
{
    caldera::caldera(std::string p_title)
        : glfw(p_title)
        , m_renderer({p_title, 20210328, debug::none, required_extensions(), create_surface_maker(), framebuffer})
    {
    }

    void caldera::draw() { m_renderer.add_uniform(&size); }

    void caldera::render() { m_renderer.render(); }

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
        return [&](vk::Instance p_instance) -> vk::SurfaceKHR {
            VkSurfaceKHR surface;
            glfwCreateWindowSurface(p_instance, handle(), nullptr, &surface);
            return surface;
        };
    }
}  // namespace caldera