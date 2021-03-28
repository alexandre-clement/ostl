#pragma once

#include <string>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glass/glass.hpp>

#include "glfw/glfw.hpp"
#include "vulkan/vulkan.hpp"

namespace caldera
{
    template<class window, class renderer>
    class base : public window
    {
    public:
        base(std::string p_title)
            : window(p_title)
            , m_renderer(configuration{
                p_title,
                20210328,
                debug::none,
                this->required_extensions(),
                this->meta_surface_maker<renderer::surface, renderer::instance>()})
        {
        }

        virtual ~base() = default;

        void draw() override {}

    private:
        renderer m_renderer;
    };

    using caldera = base<glfw, vulkan>;
}  // namespace caldera