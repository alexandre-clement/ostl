#pragma once

#include <functional>

#include "dsl/matrix.hpp"

namespace ostl
{
    struct ray_hit
    {
        vec3 ray_origin;
        vec3 ray_direction;
        vec3 position;
        float distance;
        int number_of_steps;
    };

    using texture = std::function<vec4(ray_hit)>;
}  // namespace ostl