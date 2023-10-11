#pragma once

#include <vector>

#include "../model/utility.hpp"
#include "code_element.hpp"
#include "statement.hpp"

namespace keros
{
    template<complete_model base>
    class statement_list : public code_element<base>
    {
    public:
        statement_list() = default;
        statement_list(const statement_list&) = default;
        statement_list(statement_list&&) noexcept = default;
        statement_list& operator=(const statement_list&) = default;
        statement_list& operator=(statement_list&&) noexcept = default;
        ~statement_list() = default;

        using guest_ref = typename base::guest_ref;

        std::vector<ptr<statement<base>>> statements;

        make_visitable
    };
}  // namespace keros