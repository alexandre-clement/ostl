#pragma once

#include <stdint.h>
#include <string>
#include <vector>

#include "debug.hpp"
#include "utility.hpp"

namespace caldera
{
    struct configuration
    {
        std::string name;
        std::uint32_t version;
        debug debug_mode;
        std::vector<c_str> required_extensions;
        surface_maker create_surface;
    };
}  // namespace caldera