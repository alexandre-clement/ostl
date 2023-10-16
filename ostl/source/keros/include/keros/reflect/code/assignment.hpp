#pragma once

#include <string>
#include <utility>

#include "../declaration/variable.hpp"
#include "expression.hpp"
#include "right_hand_side_receiver.hpp"
#include "statement.hpp"
#include "variable_reference.hpp"

namespace keros
{
    template<complete_model base>
    class assignment
        : public variable_reference<base>
        , public right_hand_side_receiver<base>
        , public statement<base>
    {
    public:
        template<derived_from<type<base>> derived>
        assignment(std::string p_name, derived p_return_type)
            : variable_reference<base>(std::move(p_name), p_return_type)
        {
        }
        assignment(const assignment&) = default;
        assignment(assignment&&) noexcept = default;
        assignment& operator=(const assignment&) = default;
        assignment& operator=(assignment&&) noexcept = default;
        ~assignment() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros