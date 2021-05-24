#pragma once

#include "model.hpp"

namespace keros
{
    // unspecialize a template class
    // this transform [t = template_type<unknown_type>] -> template<class u> template_type;
    template<class t>
    struct unspecialize;

    template<template<class...> class template_type, class unknown_type>
    struct unspecialize<template_type<unknown_type>>
    {
        template<class u>
        using type = template_type<u>;
    };

    // unspecialize a template from `t` and apply it to `u`.
    // this transform [t = template_type<unknown_type>] -> template_type<u>;
    template<class t, class u>
    using unspecialize_t = typename unspecialize<t>::template type<u>;

    // retrieve the base type from an element of the model
    template<class t>
    struct retrieve_base;

    template<template<class...> class pointer, template<class> class... elements, template<class> class t>
    struct retrieve_base<t<model<pointer, elements...>>>
    {
        using type = model<pointer, elements...>;
    };

    template<template<class...> class pointer, template<class> class... elements, template<class> class t>
    struct retrieve_base<pointer<t<model<pointer, elements...>>>>
    {
        using type = model<pointer, elements...>;
    };

    // retrieve the base type from a type `t` of the model.
    template<class t>
    using base_of = typename retrieve_base<std::decay_t<t>>::type;

    // retrieve the pointer type from an element of the model
    template<class t>
    struct retrieve_base_pointer;

    template<template<class...> class pointer, template<class> class... elements, template<class> class t>
    struct retrieve_base_pointer<t<model<pointer, elements...>>>
    {
        template<class u>
        using type = pointer<u>;
    };

    template<template<class...> class pointer, template<class> class... elements>
    struct retrieve_base_pointer<model<pointer, elements...>>
    {
        template<class u>
        using type = pointer<u>;
    };

    // retrieve the pointer type from a type `t` of the model and apply it to `u`.
    template<class t, class u>
    using apply_pointer_to = typename retrieve_base_pointer<t>::template type<u>;

    // retrieve the pointer type from a type `t` of the model and apply it to itself.
    template<class t>
    using pointer_on = apply_pointer_to<t, t>;

    // define ptr as an alias for pointer_on
    template<class t>
    using ptr = pointer_on<t>;

    template<class base, class derived>
    struct is_base_of : std::bool_constant<false>
    {
    };

    template<template<class> class base, template<class> class derived, template<class...> class pointer, template<class> class... elements>
    struct is_base_of<pointer<base<model<pointer, elements...>>>, pointer<derived<model<pointer, elements...>>>>
        : std::bool_constant<std::is_base_of<base<model<pointer, elements...>>, derived<model<pointer, elements...>>>::value>
    {
    };

    template<class base, class derived>
    constexpr bool is_base_of_v = is_base_of<base, derived>::value;

    template<class derived_ptr, class base>
    concept derived_from = is_base_of_v<ptr<base>, derived_ptr>;
}  // namespace keros
