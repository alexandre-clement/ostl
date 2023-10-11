#pragma once

#include "refect/model/model.hpp"

namespace keros
{
    template<complete_model base>
    class factory
    {
    public:
        factory() = default;
        factory(const factory&) = default;
        factory(factory&&) noexcept = default;
        factory& operator=(const factory&) = default;
        factory& operator=(factory&&) noexcept = default;
        ~factory() = default;
    };
}  // namespace keros