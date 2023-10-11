#pragma once

#include "code_element.hpp"

namespace keros
{
    template<complete_model base>
    class statement : public code_element<base>
    {
    public:
        statement() = default;
        statement(const statement&) = default;
        statement(statement&&) noexcept = default;
        statement& operator=(const statement&) = default;
        statement& operator=(statement&&) noexcept = default;
        ~statement() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros