#pragma once

#include <stdint.h>
#include <string>
#include <vector>

#include <vulkan/vulkan.hpp>

#include <detail/detail.hpp>

#include "configuration.hpp"
#include "utility.hpp"

namespace caldera
{
    class vulkan : private detail::loggable<vulkan>
    {
    public:
        using instance = vk::Instance;
        using surface = vk::SurfaceKHR::CType;

        vulkan(configuration);
        ~vulkan();

    private:
        void create_instance();

        configuration m_configuration;
        const std::string engine_name = "caldera";
        const std::uint32_t engine_version = caldera_version;

        instance m_instance;
        vk::SurfaceKHR m_surface;
    };
}  // namespace caldera