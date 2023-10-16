#pragma once

#include <string>
#include <utility>
#include <vector>

#include "expression.hpp"
#include "reference.hpp"
#include "statement.hpp"

namespace keros
{
    template<complete_model base>
    class invocation
        : public reference<base>
        , public statement<base>
        , public expression<base>
    {
    public:
        template<derived_from<type<base>> derived>
        invocation(std::string p_name, derived p_return_type)
            : reference<base>(std::move(p_name))
            , expression<base>(p_return_type)
        {
        }
        invocation(const invocation&) = default;
        invocation(invocation&&) noexcept = default;
        invocation& operator=(const invocation&) = default;
        invocation& operator=(invocation&&) noexcept = default;
        ~invocation() = default;

        using guest_ref = typename base::guest_ref;

        template<derived_from<expression<base>> derived>
        invocation* add_argument(derived p_argument)
        {
            arguments.push_back(p_argument);
            return this;
        }

        std::vector<ptr<expression<base>>> arguments;

        make_visitable
    };
}  // namespace keros