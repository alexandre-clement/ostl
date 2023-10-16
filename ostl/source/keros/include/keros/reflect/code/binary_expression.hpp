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
    class logical_and : public binary_expression<base>
    {
    public:
        template<derived_from<type<base>> derived>
        logical_and(derived p_return_type) : binary_expression<base>(p_return_type)
        {
        }
        logical_and(const logical_and&) = default;
        logical_and(logical_and&&) noexcept = default;
        logical_and& operator=(const logical_and&) = default;
        logical_and& operator=(logical_and&&) noexcept = default;
        ~logical_and() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };

    template<complete_model base>
    class binary_and : public binary_expression<base>
    {
    public:
        template<derived_from<type<base>> derived>
        binary_and(derived p_return_type) : binary_expression<base>(p_return_type)
        {
        }
        binary_and(const binary_and&) = default;
        binary_and(binary_and&&) noexcept = default;
        binary_and& operator=(const binary_and&) = default;
        binary_and& operator=(binary_and&&) noexcept = default;
        ~binary_and() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };

    template<complete_model base>
    class binary_right_shift : public binary_expression<base>
    {
    public:
        template<derived_from<type<base>> derived>
        binary_right_shift(derived p_return_type) : binary_expression<base>(p_return_type)
        {
        }
        binary_right_shift(const binary_right_shift&) = default;
        binary_right_shift(binary_right_shift&&) noexcept = default;
        binary_right_shift& operator=(const binary_right_shift&) = default;
        binary_right_shift& operator=(binary_right_shift&&) noexcept = default;
        ~binary_right_shift() = default;

        using guest_ref = typename base::guest_ref;

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

    template<complete_model base>
    class substraction : public binary_expression<base>
    {
    public:
        template<derived_from<type<base>> derived>
        substraction(derived p_return_type) : binary_expression<base>(p_return_type)
        {
        }
        substraction(const substraction&) = default;
        substraction(substraction&&) noexcept = default;
        substraction& operator=(const substraction&) = default;
        substraction& operator=(substraction&&) noexcept = default;
        ~substraction() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };

    template<complete_model base>
    class multiplication : public binary_expression<base>
    {
    public:
        template<derived_from<type<base>> derived>
        multiplication(derived p_return_type) : binary_expression<base>(p_return_type)
        {
        }
        multiplication(const multiplication&) = default;
        multiplication(multiplication&&) noexcept = default;
        multiplication& operator=(const multiplication&) = default;
        multiplication& operator=(multiplication&&) noexcept = default;
        ~multiplication() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };

    template<complete_model base>
    class less_than : public binary_expression<base>
    {
    public:
        template<derived_from<type<base>> derived>
        less_than(derived p_return_type) : binary_expression<base>(p_return_type)
        {
        }
        less_than(const less_than&) = default;
        less_than(less_than&&) noexcept = default;
        less_than& operator=(const less_than&) = default;
        less_than& operator=(less_than&&) noexcept = default;
        ~less_than() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros