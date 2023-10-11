#pragma once

#include "../model/element.hpp"

namespace keros
{
    template<complete_model base>
    class code_element : public virtual element<base>
    {
    public:
        code_element() = default;
        code_element(const code_element&) = default;
        code_element(code_element&&) noexcept = default;
        code_element& operator=(const code_element&) = default;
        code_element& operator=(code_element&&) noexcept = default;
        ~code_element() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros