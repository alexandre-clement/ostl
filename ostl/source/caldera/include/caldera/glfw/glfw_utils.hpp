#pragma once

#include <cstdint>
#include <vector>

#include <glass/glass.hpp>

namespace caldera
{
    glass::keyboard::key glfw_key_convert(int key);
}  // namespace caldera