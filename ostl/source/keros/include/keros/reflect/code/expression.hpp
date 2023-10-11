#pragma once

#include "../declaration/typed.hpp"

namespace keros
{
    template<complete_model base>
    class expression : public typed<base>
    {
    public:
        template<derived_from<type<base>> derived>
        expression(derived p_return_type) : typed<base>(p_return_type)
        {
        }
        expression(const expression&) = default;
        expression(expression&&) noexcept = default;
        expression& operator=(const expression&) = default;
        expression& operator=(expression&&) noexcept = default;
        ~expression() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros