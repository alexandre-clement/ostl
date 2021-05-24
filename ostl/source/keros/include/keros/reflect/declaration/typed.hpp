#pragma once

#include "../model/element.hpp"
#include "../model/utility.hpp"
#include "type.hpp"

namespace keros
{
    template<complete_model base>
    class typed : public virtual element<base>
    {
    public:
        template<derived_from<type<base>> derived>
        typed(derived p_type) : typeof(p_type)
        {
        }
        typed(const typed&) = default;
        typed(typed&&) noexcept = default;
        typed& operator=(const typed&) = default;
        typed& operator=(typed&&) noexcept = default;
        ~typed() = default;

        using guest_ref = typename base::guest_ref;

        ptr<type<base>> typeof;

        make_visitable
    };
}  // namespace keros