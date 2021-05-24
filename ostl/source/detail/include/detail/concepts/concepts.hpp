#pragma once

#include <concepts>
#include <type_traits>

namespace detail
{
    template<class t>
    concept iterable = requires(t i)
    {
        i.begin();
        i.end();
    };

    template<class t>
    concept arithmetic = std::is_arithmetic_v<t>;
}  // namespace detail