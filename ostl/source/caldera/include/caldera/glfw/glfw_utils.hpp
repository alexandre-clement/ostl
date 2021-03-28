#pragma once

#include <cstdint>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glass/glass.hpp>

namespace caldera
{
    glass::keyboard::key glfw_key_convert(int key);

    std::vector<const char*> glfw_required_extensions();
}  // namespace caldera