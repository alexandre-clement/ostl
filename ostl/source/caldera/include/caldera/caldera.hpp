#pragma once

#include <string>

#define GLFW_INCLUDE_VULKAN
#include "glfw/glfw.hpp"
#include "vulkan/vulkan.hpp"

namespace caldera
{
    class caldera
        : public glfw
        , private detail::loggable<caldera>
    {
    public:
        caldera(std::string p_title);
        caldera(std::string p_title, std::uint32_t);
        virtual ~caldera() = default;

        void draw(const glass::shader&) override;

        void render() override;

    private:
        surface_maker create_surface_maker();
        idle create_idle();
        [[nodiscard]] std::vector<const char*> required_extensions() const;

        vulkan m_renderer;
    };
}  // namespace caldera