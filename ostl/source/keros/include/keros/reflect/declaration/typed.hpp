#pragma once

#include "../model/element.hpp"
#include "type.hpp"

#define property

namespace keros
{
    template<complete_model base>
    class typed : public virtual element<base>
    {
    public:
        typed() = default;
        typed(const typed&) = default;
        typed(typed&&) noexcept = default;
        typed& operator=(const typed&) = default;
        typed& operator=(typed&&) noexcept = default;
        ~typed() = default;

        using guest_ref = typename base::guest_ref;

        type typeof;

        make_visitable
    };
}  // namespace keros