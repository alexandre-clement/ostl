#pragma once

#include <string>
#include <utility>

#include "code_element.hpp"

namespace keros
{
    template<complete_model base>
    class reference : public code_element<base>
    {
    public:
        reference(std::string p_name) : name(std::move(p_name)) {}
        reference(const reference&) = default;
        reference(reference&&) noexcept = default;
        reference& operator=(const reference&) = default;
        reference& operator=(reference&&) noexcept = default;
        ~reference() = default;

        using guest_ref = typename base::guest_ref;

        std::string name;

        make_visitable
    };
}  // namespace keros