#pragma once

#include <tuple>
#include <type_traits>

namespace detail
{
    template<class container, class e>
    struct contains;

    template<template<class...> class container, class e>
    struct contains<container<>, e> : std::false_type
    {
    };

    template<template<class...> class container, class head, class... tail, class e>
    struct contains<container<head, tail...>, e>
        : std::integral_constant<bool, std::is_same_v<head, e> || contains<container<tail...>, e>::value>
    {
    };

    template<class container, class e>
    constexpr bool contains_v = contains<container, e>::value;

    namespace _
    {
        template<class container, class result>
        struct tuple_to_set;

        template<template<class...> class container, class result>
        struct tuple_to_set<container<>, result>
        {
            using type = result;
        };

        template<template<class...> class container, class head, class... tail, class... result_types>
        struct tuple_to_set<container<head, tail...>, container<result_types...>>
        {
            using type = std::conditional_t<contains_v<container<result_types...>, head>,
              typename tuple_to_set<container<tail...>, container<result_types...>>::type,
              typename tuple_to_set<container<tail...>, container<result_types..., head>>::type>;
        };

        template<class container>
        struct set;

        template<template<class...> class container, class... elements>
        struct set<container<elements...>>
        {
            using type = typename tuple_to_set<container<elements...>, container<>>::type;
        };
    }  // namespace _

    template<class container>
    using set = typename _::set<container>::type;
}  // namespace detail
