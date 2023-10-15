#pragma once

#include "../model/element.hpp"

namespace keros
{
    template<complete_model base>
    class right_hand_side_receiver : public virtual element<base>
    {
    public:
        right_hand_side_receiver() = default;
        right_hand_side_receiver(const right_hand_side_receiver&) = default;
        right_hand_side_receiver(right_hand_side_receiver&&) noexcept = default;
        right_hand_side_receiver& operator=(const right_hand_side_receiver&) = default;
        right_hand_side_receiver& operator=(right_hand_side_receiver&&) noexcept = default;
        ~right_hand_side_receiver() = default;

        using guest_ref = typename base::guest_ref;

        ptr<expression<base>> right_hand_side;

        make_visitable
    };
}  // namespace keros