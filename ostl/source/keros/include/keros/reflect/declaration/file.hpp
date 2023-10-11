#pragma once

#include <vector>

#include "../code/directive.hpp"
#include "../model/element.hpp"
#include "../model/utility.hpp"
#include "function.hpp"
#include "named.hpp"

namespace keros
{
    template<complete_model base>
    class file final : public statement_list<base>
    {
    public:
        file() = default;
        file(const file&) = default;
        file(file&&) noexcept = default;
        file& operator=(const file&) = default;
        file& operator=(file&&) noexcept = default;
        ~file() = default;

        using guest_ref = typename base::guest_ref;

        file* add_directive(const ptr<directive<base>> p_directive)
        {
            directives.push_back(p_directive);
            return this;
        }

        file* add_function(const ptr<function<base>> p_function)
        {
            functions.push_back(p_function);
            return this;
        }

        std::vector<ptr<directive<base>>> directives;
        std::vector<ptr<function<base>>> functions;

        make_visitable
    };
}  // namespace keros