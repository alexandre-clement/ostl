#pragma once

#include "../model/utility.hpp"
#include "expression.hpp"
#include "statement.hpp"

namespace keros
{
    template<complete_model base>
    class if_ : public statement<base>
    {
    public:
        if_() = default;
        if_(const if_&) = default;
        if_(if_&&) noexcept = default;
        if_& operator=(const if_&) = default;
        if_& operator=(if_&&) noexcept = default;
        ~if_() = default;

        using guest_ref = typename base::guest_ref;

        ptr<expression<base>> condition;
        ptr<statement<base>> then;
        ptr<statement<base>> else_ = nullptr;

        make_visitable
    };
}  // namespace keros
