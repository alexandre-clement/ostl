#pragma once

#include "visitor.hpp"

namespace detail
{
    namespace _
    {
        template<class g, class f, class visitables, class queue>
        class g_compound;

        template<class g, class f, class visitables, class queue>
        class f_compound;

        template<class g, class f, class visitables>
        class g_compound<g, f, visitables, pack<>> : public g
        {
        public:
            using g::visit;

            g_compound(f& p_caller) : caller(p_caller) {}

        protected:
            f& caller;
        };

        template<class g, class f, class visitables, class head, class... tail>
        class g_compound<g, f, visitables, pack<head, tail...>> : public g_compound<g, f, visitables, pack<tail...>>
        {
        public:
            using g_compound<g, f, visitables, pack<tail...>>::g_compound;
            using g_compound<g, f, visitables, pack<tail...>>::visit;

            void visit(const head& host) override { this->caller.visit(host); }

            void bounce(const head& host) { g::visit(host); }
        };

        template<class g, class f, class visitables, class head, class body, class... tail>
        class g_compound<g, f, visitables, pack<head, body, tail...>> : public g_compound<g, f, visitables, pack<body, tail...>>
        {
        public:
            using g_compound<g, f, visitables, pack<body, tail...>>::g_compound;
            using g_compound<g, f, visitables, pack<body, tail...>>::bounce;
            using g_compound<g, f, visitables, pack<body, tail...>>::visit;

            void visit(const head& host) override { this->caller.visit(host); }

            void bounce(const head& host) { g::visit(host); }
        };

        template<class g, class f, class visitables>
        class f_compound<g, f, visitables, pack<>> : public f
        {
        public:
            using f::visit;

            f_compound() : trampoline(*this) {}

        protected:
            g_compound<g, f, visitables, visitables> trampoline;
        };

        template<class g, class f, class visitables, class head, class... tail>
        class f_compound<g, f, visitables, pack<head, tail...>> : public f_compound<g, f, visitables, pack<tail...>>
        {
        public:
            using f_compound<g, f, visitables, pack<tail...>>::visit;

            void visit(const head& host) override
            {
                f::visit(host);
                this->trampoline.bounce(host);
            }
        };
    }  // namespace _

    // compose<g, f> =  g o f
    template<class g, class f>
    class compose;

    // compose<g, f> =  g o f
    template<class g, class f, class... elements>
    class explicit_compose : public _::f_compound<g, f, pack<elements...>, pack<elements...>>
    {
    };
}  // namespace detail
