#pragma once

#include "model.hpp"

namespace keros
{
    template<complete_model base>
    class element : public base
    {
    public:
        element() = default;
        element(const element&) = default;
        element(element&&) noexcept = default;
        element& operator=(const element&) = default;
        element& operator=(element&&) noexcept = default;
        ~element() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros