#pragma once

#include "../model/element.hpp"
#include "../model/utility.hpp"
#include "code_block.hpp"

namespace keros
{
    template<complete_model base>
    class body_holder : public virtual element<base>
    {
    public:
        body_holder() = default;
        body_holder(const body_holder&) = default;
        body_holder(body_holder&&) noexcept = default;
        body_holder& operator=(const body_holder&) = default;
        body_holder& operator=(body_holder&&) noexcept = default;
        ~body_holder() = default;

        using guest_ref = typename base::guest_ref;

        code_block<base> body;

        make_visitable
    };
}  // namespace keros