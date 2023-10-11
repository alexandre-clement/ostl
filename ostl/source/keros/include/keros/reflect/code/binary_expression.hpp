#pragma once

#include "expression.hpp"

namespace keros
{
    template<complete_model base>
    class binary_expression : public expression<base>
    {
    public:
        template<derived_from<type<base>> derived>
        binary_expression(derived p_return_type) : expression<base>(p_return_type)
        {
        }
        binary_expression(const binary_expression&) = default;
        binary_expression(binary_expression&&) noexcept = default;
        binary_expression& operator=(const binary_expression&) = default;
        binary_expression& operator=(binary_expression&&) noexcept = default;
        ~binary_expression() = default;

        using guest_ref = typename base::guest_ref;

        ptr<expression<base>> left;
        ptr<expression<base>> right;

        make_visitable
    };

    template<complete_model base>
    class addition : public binary_expression<base>
    {
    public:
        template<derived_from<type<base>> derived>
        addition(derived p_return_type) : binary_expression<base>(p_return_type)
        {
        }
        addition(const addition&) = default;
        addition(addition&&) noexcept = default;
        addition& operator=(const addition&) = default;
        addition& operator=(addition&&) noexcept = default;
        ~addition() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros