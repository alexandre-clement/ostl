#pragma once

#include <cstdint>

#ifndef CALDERA_VERSION
    #define CALDERA_VERSION "19700101"
#endif

namespace caldera
{
    using c_str = const char*;

    const std::uint32_t caldera_version = std::stoi(CALDERA_VERSION);
}  // namespace caldera