#pragma once

#include "../model/element.hpp"

namespace keros
{
    template<complete_model base>
    class shader final : public element<base>
    {
    public:
        shader() = default;
        shader(const shader&) = default;
        shader(shader&&) noexcept = default;
        shader& operator=(const shader&) = default;
        shader& operator=(shader&&) noexcept = default;
        ~shader() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros