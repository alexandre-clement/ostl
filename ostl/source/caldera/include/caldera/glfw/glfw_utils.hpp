#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glass/glass.hpp>

namespace caldera
{
    glass::keyboard::key glfw_key_convert(int key);
}  // namespace caldera