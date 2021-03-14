#pragma once

#include <abacus/abacus.hpp>

namespace ostl
{
    template<class _scalar_type, abacus::index _rows, abacus::index _columns>
    class matrix
    {
    };

    using vec2 = matrix<float, 1, 2>;
    using vec3 = matrix<float, 1, 3>;
    using vec4 = matrix<float, 1, 4>;

    using mat2x2 = matrix<float, 2, 2>;
    using mat2x3 = matrix<float, 2, 3>;
    using mat2x4 = matrix<float, 2, 4>;
    using mat2 = mat2x2;

    using mat3x2 = matrix<float, 3, 2>;
    using mat3x3 = matrix<float, 3, 3>;
    using mat3x4 = matrix<float, 3, 4>;
    using mat3 = mat3x3;

    using mat4x2 = matrix<float, 4, 2>;
    using mat4x3 = matrix<float, 4, 3>;
    using mat4x4 = matrix<float, 4, 4>;
    using mat4 = mat4x4;
}  // namespace ostl