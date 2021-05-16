#pragma once

#include "../model/element.hpp"

namespace keros
{
    template<complete_model base>
    class file final : public element<base>
    {
    public:
        file() = default;
        file(const file&) = default;
        file(file&&) noexcept = default;
        file& operator=(const file&) = default;
        file& operator=(file&&) noexcept = default;
        ~file() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros