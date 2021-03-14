#pragma once

namespace detail
{
    namespace _
    {
        template<class collection, class new_element>
        struct append;

        template<template<class...> class collection, class... current_elements, class new_element>
        struct append<collection<current_elements...>, new_element>
        {
            using type = collection<current_elements..., new_element>;
        };

        template<class collection, class new_element>
        struct preppend;

        template<template<class...> class collection, class... current_elements, class new_element>
        struct preppend<collection<current_elements...>, new_element>
        {
            using type = collection<new_element, current_elements...>;
        };
    }  // namespace _

    template<class collection, class new_element>
    using append = typename _::append<collection, new_element>::type;

    template<class collection, class new_element>
    using preppend = typename _::preppend<collection, new_element>::type;

    namespace _
    {
        template<class... tuples>
        struct merge;

        template<template<class...> class collection>
        struct merge<collection<>>
        {
            using type = collection<>;
        };

        template<template<class...> class collection, class... tuples>
        struct merge<collection<>, tuples...>
        {
            using type = typename merge<tuples...>::type;
        };

        template<template<class...> class collection, class head, class... tail, class... tuples>
        struct merge<collection<head, tail...>, tuples...>
        {
            using type = typename preppend<typename merge<collection<tail...>, tuples...>::type, head>::type;
        };
    }  // namespace _

    template<class... tuples>
    using merge = typename _::merge<tuples...>::type;
}  // namespace detail