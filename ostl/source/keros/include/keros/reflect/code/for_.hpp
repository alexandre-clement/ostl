#pragma once

#include "../model/utility.hpp"
#include "body_holder.hpp"
#include "expression.hpp"
#include "statement.hpp"

namespace keros
{
    template<complete_model base>
    class for_
        : public statement<base>
        , public body_holder<base>
    {
    public:
        for_() = default;
        for_(const for_&) = default;
        for_(for_&&) noexcept = default;
        for_& operator=(const for_&) = default;
        for_& operator=(for_&&) noexcept = default;
        ~for_() = default;

        using guest_ref = typename base::guest_ref;

        ptr<expression<base>> initializer;
        ptr<expression<base>> halt_condition;
        ptr<expression<base>> increment;

        make_visitable
    };
}  // namespace keros