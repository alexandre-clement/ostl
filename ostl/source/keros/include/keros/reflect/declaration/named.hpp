#pragma once

#include <string>
#include <utility>

#include "../model/element.hpp"

namespace keros
{
    template<complete_model base>
    class named : public virtual element<base>
    {
    public:
        named(std::string p_name) : name(std::move(p_name)) {}
        named(const named&) = default;
        named(named&& p_named) noexcept = default;
        named& operator=(const named&) = default;
        named& operator=(named&&) noexcept = default;
        ~named() = default;

        using guest_ref = typename base::guest_ref;

        std::string name;

        make_visitable
    };
}  // namespace keros