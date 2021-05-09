#pragma once

#include <detail/detail.hpp>

namespace keros
{
    template<class t>
    constexpr bool is_complete_model = false;

    template<class t>
    concept complete_model = is_complete_model<t>;

    template<template<class...> class pointer, template<class> class... elements>
    struct model : detail::visitable<detail::pack<elements<model<pointer, elements...>>...>, detail::qualifier::constant>
    {
    };

    template<template<class...> class pointer, template<class> class... elements>
    constexpr bool is_complete_model<model<pointer, elements...>> = true;
}  // namespace keros
