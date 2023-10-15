#pragma once

#include "code_element.hpp"

namespace keros
{
    template<complete_model base>
    class modifier : public code_element<base>
    {
    public:
        modifier() = default;
        modifier(const modifier&) = default;
        modifier(modifier&&) noexcept = default;
        modifier& operator=(const modifier&) = default;
        modifier& operator=(modifier&&) noexcept = default;
        ~modifier() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };

    template<complete_model base>
    class uniform : public modifier<base>
    {
    public:
        uniform() = default;
        uniform(const uniform&) = default;
        uniform(uniform&&) noexcept = default;
        uniform& operator=(const uniform&) = default;
        uniform& operator=(uniform&&) noexcept = default;
        ~uniform() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros