#pragma once

#include <string>

#define GLFW_INCLUDE_VULKAN
#include "glfw/glfw.hpp"
#include "vulkan/vulkan.hpp"

namespace caldera
{
    class caldera : public glfw
    {
    public:
        caldera(std::string p_title);
        virtual ~caldera() = default;

        void draw() override;

    private:
        surface_maker create_surface_maker();
        [[nodiscard]] std::vector<const char*> required_extensions() const;

        vulkan m_renderer;
    };
}  // namespace caldera