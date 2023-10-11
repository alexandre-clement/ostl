#pragma once

#include "statement.hpp"
#include "statement_list.hpp"

namespace keros
{
    template<complete_model base>
    class code_block
        : public statement<base>
        , public statement_list<base>
    {
    public:
        code_block() = default;
        code_block(const code_block&) = default;
        code_block(code_block&&) noexcept = default;
        code_block& operator=(const code_block&) = default;
        code_block& operator=(code_block&&) noexcept = default;
        ~code_block() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros