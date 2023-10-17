#pragma once

#include <string>

#include "matrix.hpp"

namespace ostl
{
    template<class element>
    std::string to_glsl(element);

    template<>
    std::string to_glsl(vec2 p_vec2)
    {
        return "vec2 local_variable_1 = vec2()";
    }
}  // namespace ostl