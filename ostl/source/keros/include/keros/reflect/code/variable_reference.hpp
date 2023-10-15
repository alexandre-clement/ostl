#pragma once

#include <string>
#include <utility>

#include "expression.hpp"
#include "reference.hpp"
#include "statement.hpp"

namespace keros
{
    template<complete_model base>
    class variable_reference
        : public reference<base>
        , public expression<base>
        , public statement<base>
    {
    public:
        template<derived_from<type<base>> derived>
        variable_reference(derived p_return_type, std::string p_name)
            : expression<base>(p_return_type)
            , reference<base>(std::move(p_name))
        {
        }
        variable_reference(const variable_reference&) = default;
        variable_reference(variable_reference&&) noexcept = default;
        variable_reference& operator=(const variable_reference&) = default;
        variable_reference& operator=(variable_reference&&) noexcept = default;
        ~variable_reference() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros