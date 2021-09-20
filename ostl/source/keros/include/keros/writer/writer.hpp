#pragma once

#include <functional>

#include "../reflect/declaration/shader.hpp"
#include "context.hpp"
#include "type.hpp"

namespace keros
{
    template<complete_model base>
    class writer
    {
    public:
        shader<base> vertex(std::function<void(context)>) { return shader<base>(); }

        shader<base> fragment(std::function<void(context)>) { return shader<base>(); }
    };
}  // namespace keros