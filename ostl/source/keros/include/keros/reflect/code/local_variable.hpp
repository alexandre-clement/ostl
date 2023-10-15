#pragma once

#include <string>
#include <utility>

#include "../declaration/variable.hpp"
#include "expression.hpp"
#include "right_hand_side_receiver.hpp"
#include "statement.hpp"

namespace keros
{
    template<complete_model base>
    class local_variable
        : public variable<base>
        , public right_hand_side_receiver<base>
        , public statement<base>
        , public expression<base>
    {
    public:
        template<derived_from<type<base>> derived>
        local_variable(std::string p_name, derived p_return_type)
            : variable<base>(std::move(p_name), p_return_type)
            , expression<base>(p_return_type)
        {
        }
        local_variable(const local_variable&) = default;
        local_variable(local_variable&&) noexcept = default;
        local_variable& operator=(const local_variable&) = default;
        local_variable& operator=(local_variable&&) noexcept = default;
        ~local_variable() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros