#include "ostl/object/sphere.hpp"

#include <utility>

namespace ostl
{
    constexpr sphere::sphere(abacus::vec3 p_position) : position(std::move(p_position)) {}

    constexpr sphere::sphere(float p_radius) : radius(p_radius) {}

    constexpr sphere::sphere(abacus::vec3 p_position, float p_radius)
        : position(std::move(p_position))
        , radius(p_radius)
    {
    }
}  // namespace ostl