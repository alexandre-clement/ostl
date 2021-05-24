#pragma once

#include "named.hpp"

namespace keros
{
    template<complete_model base>
    class type : public named<base>
    {
    public:
        type(std::string p_name) : named<base>(std::move(p_name)) {}
        type(const type&) = default;
        type(type&&) noexcept = default;
        type& operator=(const type&) = default;
        type& operator=(type&&) noexcept = default;
        ~type() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros