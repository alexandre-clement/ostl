#pragma once

#include "modifiable.hpp"
#include "named.hpp"
#include "typed.hpp"

namespace keros
{
    template<complete_model base>
    class variable
        : public named<base>
        , public typed<base>
        , public modifiable<base>
    {
    public:
        template<derived_from<type<base>> derived>
        variable(std::string p_name, derived p_return_type) : named<base>(std::move(p_name))
                                                            , typed<base>(p_return_type)
        {
        }
        variable(const variable&) = default;
        variable(variable&&) noexcept = default;
        variable& operator=(const variable&) = default;
        variable& operator=(variable&&) noexcept = default;
        ~variable() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros