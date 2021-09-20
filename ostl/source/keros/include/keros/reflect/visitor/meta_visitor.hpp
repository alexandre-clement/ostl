#pragma once

#include "scanner.hpp"

#define make_visitor(visitor_class)                                                                                    \
    template<::keros::complete_model base>                                                                             \
    class visitor_class;                                                                                               \
                                                                                                                       \
    template<::keros::complete_model base, class... hosts>                                                             \
    class visitor_class##_implementation;                                                                              \
                                                                                                                       \
    template<::keros::complete_model base, class head, class... tail>                                                  \
    class visitor_class##_implementation<base, head, tail...> : public visitor_class##_implementation<base, tail...>   \
    {                                                                                                                  \
    public:                                                                                                            \
        using visitor_class##_implementation<base, tail...>::visit;                                                    \
                                                                                                                       \
        void visit(const head&) override {}                                                                            \
    };                                                                                                                 \
                                                                                                                       \
    template<template<class...> class pointer, template<class> class... elements>                                      \
    class visitor_class<model<pointer, elements...>>                                                                   \
        : public visitor_class##_implementation<model<pointer, elements...>, elements<model<pointer, elements...>>...> \
    {                                                                                                                  \
    };                                                                                                                 \
                                                                                                                       \
    template<::keros::complete_model base>                                                                             \
    class visitor_class##_implementation<base> : public ::keros::scanner<visitor_class<base>, base>

#define overload(visitor_class, overload_type)                                                                         \
    template<::keros::complete_model base, class... tail>                                                              \
    class visitor_class##_implementation<base, overload_type<base>, tail...>                                           \
        : public visitor_class##_implementation<base, tail...>                                                         \
    {                                                                                                                  \
    public:                                                                                                            \
        using visitor_class##_implementation<base, tail...>::visit;                                                    \
                                                                                                                       \
        void visit(const overload_type<base>&) override;                                                               \
    };                                                                                                                 \
                                                                                                                       \
    template<::keros::complete_model base, class... tail>                                                              \
    void visitor_class##_implementation<base, overload_type<base>, tail...>::visit([[maybe_unused]] const overload_type<base>& host)
