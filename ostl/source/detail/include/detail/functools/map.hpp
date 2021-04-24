#pragma once

#include <functional>

#include "detail/itertools/enumerate.hpp"

namespace detail
{
    template<class input_type, template<class...> class container, class output_type>
    container<output_type> map(const container<input_type>& p_container, std::function<output_type(const input_type&)> f)
    {
        container<output_type> result;
        for (const input_type& input_value : p_container)
        {
            result.push_back(std::move(f(input_value)));
        }
        return result;
    }
}  // namespace detail