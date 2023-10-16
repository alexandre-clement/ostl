#pragma once

#include "expression.hpp"

namespace keros
{
    template<complete_model base>
    class literal : public expression<base>
    {
    public:
        template<derived_from<type<base>> derived>
        literal(derived p_type, std::string p_value) : expression<base>(p_type)
                                                     , value(std::move(p_value))
        {
        }
        template<derived_from<type<base>> derived, class value_type>
        literal(derived p_type, value_type p_value) : literal(p_type, std::to_string(p_value))
        {
            if (value.find('.') != std::string::npos)
            {
                // remove trailing zeros in case the value is a float or a double
                value.erase(value.find_last_not_of('0') + 1, std::string::npos);
            }
        }
        literal(const literal&) = default;
        literal(literal&&) noexcept = default;
        literal& operator=(const literal&) = default;
        literal& operator=(literal&&) noexcept = default;
        ~literal() = default;

        using guest_ref = typename base::guest_ref;

        std::string value;

        make_visitable
    };
}  // namespace keros