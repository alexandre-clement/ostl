#pragma once

#include "reflect/code/literal.hpp"

namespace keros
{
    template<complete_model base>
    class literal
    {
    public:
        literal() = default;
        literal(const literal&) = default;
        literal(literal&&) noexcept = default;
        literal& operator=(const literal&) = default;
        literal& operator=(literal&&) noexcept = default;
        ~literal() = default;
    };
}  // namespace keros