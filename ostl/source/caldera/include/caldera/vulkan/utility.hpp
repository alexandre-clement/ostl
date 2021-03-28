#pragma once

#include <cstdint>
#include <functional>

#ifndef CALDERA_VERSION
    #define CALDERA_VERSION "19700101"
#endif

namespace caldera
{
    using c_str = const char*;

    const std::uint32_t caldera_version = std::stoi(CALDERA_VERSION);

    template<class surface, class instance>
    using surface_maker = std::function<surface(instance)>;
}  // namespace caldera