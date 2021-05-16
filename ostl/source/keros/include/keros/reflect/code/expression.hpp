#pragma once

#include "../declaration/typed.hpp"

namespace keros
{
    template<complete_model base>
    class expression : public typed<base>
    {
    public:
        expression() = default;
        expression(const expression&) = default;
        expression(expression&&) noexcept = default;
        expression& operator=(const expression&) = default;
        expression& operator=(expression&&) noexcept = default;
        ~expression() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros