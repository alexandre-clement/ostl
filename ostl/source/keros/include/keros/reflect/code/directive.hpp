#pragma once

#include "../model/utility.hpp"
#include "expression.hpp"
#include "statement.hpp"

namespace keros
{
    template<complete_model base>
    class directive : public statement<base>
    {
    public:
        directive() = default;
        directive(const directive&) = default;
        directive(directive&&) noexcept = default;
        directive& operator=(const directive&) = default;
        directive& operator=(directive&&) noexcept = default;
        ~directive() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };

    template<complete_model base>
    class version : public directive<base>
    {
    public:
        version(int p_value) : value(p_value) {}
        version(const version&) = default;
        version(version&&) noexcept = default;
        version& operator=(const version&) = default;
        version& operator=(version&&) noexcept = default;
        ~version() = default;

        using guest_ref = typename base::guest_ref;

        int value;

        make_visitable
    };
}  // namespace keros