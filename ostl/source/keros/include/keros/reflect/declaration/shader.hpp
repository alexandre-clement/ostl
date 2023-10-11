#pragma once

#include <vector>

#include "../model/element.hpp"
#include "../model/utility.hpp"
#include "named.hpp"

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

        std::vector<ptr<named<base>>> named_elements;

        make_visitable
    };
}  // namespace keros