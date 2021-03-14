#pragma once

#include <cstddef>
#include <type_traits>

namespace detail
{
    namespace _
    {
        template<class t, std::size_t = sizeof(t)>
        constexpr std::true_type is_complete_type(t*);

        constexpr std::false_type is_complete_type(...);
    }  // namespace _

    template<class t>
    constexpr bool is_complete = decltype(_::is_complete_type(std::declval<t*>()))::value;
}  // namespace detail