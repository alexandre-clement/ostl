#pragma once

#include <abacus/abacus.hpp>

namespace ostl
{
    class sphere
    {
    public:
        constexpr sphere() = default;
        constexpr explicit sphere(abacus::vec3);
        constexpr explicit sphere(float);
        constexpr explicit sphere(abacus::vec3, float);
        constexpr sphere(const sphere&) = default;
        constexpr sphere(sphere&&) noexcept = default;
        constexpr sphere& operator=(const sphere&) = default;
        constexpr sphere& operator=(sphere&&) noexcept = default;
        ~sphere() = default;

        abacus::vec3 position;
        float radius = 1.f;
    };
}  // namespace ostl