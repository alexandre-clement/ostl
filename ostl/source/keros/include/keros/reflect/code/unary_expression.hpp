#pragma once

#include "expression.hpp"

namespace keros
{
    template<complete_model base>
    class unary_expression : public expression<base>
    {
    public:
        template<derived_from<type<base>> derived>
        unary_expression(derived p_return_type) : expression<base>(p_return_type)
        {
        }
        unary_expression(const unary_expression&) = default;
        unary_expression(unary_expression&&) noexcept = default;
        unary_expression& operator=(const unary_expression&) = default;
        unary_expression& operator=(unary_expression&&) noexcept = default;
        ~unary_expression() = default;

        using guest_ref = typename base::guest_ref;

        ptr<expression<base>> operand;

        make_visitable
    };

    template<complete_model base>
    class prefix_increment : public unary_expression<base>
    {
    public:
        template<derived_from<type<base>> derived>
        prefix_increment(derived p_return_type) : unary_expression<base>(p_return_type)
        {
        }
        prefix_increment(const prefix_increment&) = default;
        prefix_increment(prefix_increment&&) noexcept = default;
        prefix_increment& operator=(const prefix_increment&) = default;
        prefix_increment& operator=(prefix_increment&&) noexcept = default;
        ~prefix_increment() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros