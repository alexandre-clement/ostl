#pragma once

#include <vulkan/vulkan.hpp>

#include "utility.hpp"

namespace caldera
{
    struct debugger
    {
        vk::DebugUtilsMessengerCreateInfoEXT messenger_info;
        std::vector<c_str> validation_layers;
        std::vector<c_str> extensions;

        debugger();
    };
}  // namespace caldera