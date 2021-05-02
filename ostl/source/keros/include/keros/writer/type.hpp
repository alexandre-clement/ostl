#pragma once

#include <concepts>
#include <cstddef>

#include <detail/detail.hpp>

namespace keros
{
    using index = std::size_t;

    template<index rows, index columns>
    class matrix
    {
    public:
        constexpr matrix() {}
        template<detail::arithmetic argument_type>
        constexpr explicit matrix(argument_type)
        {
        }
        template<detail::arithmetic head, detail::arithmetic body, detail::arithmetic... tail>
        constexpr matrix(head, body, tail...)
        {
        }
    };

    using vec2 = matrix<1, 2>;
    using vec4 = matrix<1, 4>;
}  // namespace keros