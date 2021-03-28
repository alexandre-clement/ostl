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
    class renderer : private detail::loggable<renderer>
    {
    public:
        renderer(configuration);
        ~renderer();

    private:
        void create_instance();

        configuration m_configuration;
        const std::string engine_name = "caldera";
        const std::uint32_t engine_version = caldera_version;

        vk::Instance m_instance;
    };
}  // namespace caldera