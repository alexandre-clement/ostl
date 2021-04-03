#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <abacus/abacus.hpp>

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
        idle wait;
        const abacus::matrix<int, 1, 2>& framebuffer;
    };
}  // namespace caldera