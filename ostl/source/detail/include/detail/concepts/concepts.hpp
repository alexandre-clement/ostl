#pragma once

#include <concepts>
#include <type_traits>

namespace detail
{
    template<class t, class base>
    concept derive_from = std::is_base_of_v<base, t>;

    template<class t>
    concept iterable = requires(t i)
    {
        i.begin();
        i.end();
    };
}  // namespace detail