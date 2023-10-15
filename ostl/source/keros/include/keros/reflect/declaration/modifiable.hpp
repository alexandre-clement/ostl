#pragma once

#include <vector>

#include "../code/modifier.hpp"
#include "../model/element.hpp"
#include "../model/utility.hpp"

namespace keros
{
    template<complete_model base>
    class modifiable : public virtual element<base>
    {
    public:
        modifiable() = default;
        modifiable(const modifiable&) = default;
        modifiable(modifiable&&) noexcept = default;
        modifiable& operator=(const modifiable&) = default;
        modifiable& operator=(modifiable&&) noexcept = default;
        ~modifiable() = default;

        using guest_ref = typename base::guest_ref;

        template<derived_from<modifier<base>> derived>
        modifiable* add_modifier(derived p_modifier)
        {
            modifiers.push_back(p_modifier);
            return this;
        }

        std::vector<ptr<modifier<base>>> modifiers;

        make_visitable
    };
}  // namespace keros