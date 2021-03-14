#pragma once

#include <detail/detail.hpp>

namespace ostl
{
    template<class drawable>
    class drawer;

    template<class t>
    concept drawable = detail::is_complete<drawer<t>>;
}  // namespace ostl