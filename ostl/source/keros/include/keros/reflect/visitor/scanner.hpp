#pragma once

#include "keros/reflect/model/model.hpp"

namespace keros
{
    template<complete_model base>
    class scanner;

    template<template<class...> class pointer, template<class> class... elements>
    class scanner<model<pointer, elements...>> : public model<pointer, elements...>::guest_type
    {
    public:
        using base = model<pointer, elements...>;

        void scan(const base& host) { host.accept(*this); }

        template<detail::derive_from<base> derived>
        void scan(const pointer<derived>& host)
        {
            host->accept(*this);
        }

        template<detail::derive_from<base> derived>
        void visit_cast(const derived& host)
        {
            this->visit(host);
        }
    };
}  // namespace keros
