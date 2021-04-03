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
        const abacus::matrix<std::uint32_t, 1, 2>& framebuffer;
    };
}  // namespace caldera