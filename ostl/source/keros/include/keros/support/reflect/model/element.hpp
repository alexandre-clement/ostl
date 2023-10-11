#pragma once

#include "refect/model/model.hpp"
#include "support/factory/factory.hpp"

namespace keros
{
    template<complete_model base>
    class element
    {
    public:
        element() = default;
        element(const element&) = default;
        element(element&&) noexcept = default;
        element& operator=(const element&) = default;
        element& operator=(element&&) noexcept = default;
        ~element() = default;

        factory<base> main_factory;
    };
}  // namespace keros