#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glass/glass.hpp>

namespace caldera
{
    glass::event::key glfw_key_convert(int key)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE:
                return glass::event::key::escape;
                break;
            default:
                return glass::event::key::unknown;
        }
    }
}  // namespace caldera