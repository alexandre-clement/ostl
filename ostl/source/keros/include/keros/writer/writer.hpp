#pragma once

#include <functional>
#include <string>

#include "scope.hpp"
#include "stage.hpp"

namespace keros
{
    template<stage t>
    class writer
    {
    public:
        void implement_main(std::function<void()>) {}

        std::string to_glsl() const { return ""; }

        scope<t, way::in> in;
        scope<t, way::out> out;
    };
}  // namespace keros