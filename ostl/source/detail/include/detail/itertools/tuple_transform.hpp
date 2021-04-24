#pragma once

#include <tuple>
#include <type_traits>

namespace detail
{
    using size = std::size_t;

    template<typename function, typename argument, size... tuple_size>
    auto tuple_transform_impl(function&& p_function, argument&& p_argument, std::index_sequence<tuple_size...>)
    {
        if constexpr (sizeof...(tuple_size) == 0)
        {
            return std::tuple<>();
        }
        else if constexpr (std::is_same_v<decltype(p_function(std::get<0>(p_argument))), void>)
        {
            (p_function(std::get<tuple_size>(p_argument)), ...);
            return;
        }
        else if constexpr (std::is_lvalue_reference_v<decltype(p_function(std::get<0>(p_argument)))>)
        {
            return std::tie(p_function(std::get<tuple_size>(p_argument))...);
        }
        else if constexpr (std::is_rvalue_reference_v<decltype(p_function(std::get<0>(p_argument)))>)
        {
            return std::forward_as_tuple(p_function(std::get<tuple_size>(p_argument))...);
        }
        else
        {
            return std::tuple(p_function(std::get<tuple_size>(p_argument))...);
        }
    }

    template<typename function, typename... values_types>
    auto tuple_transform(function&& p_function, std::tuple<values_types...>& tuple)
    {
        return tuple_transform_impl(std::forward<function>(p_function), tuple, std::make_index_sequence<sizeof...(values_types)>());
    }
}  // namespace detail