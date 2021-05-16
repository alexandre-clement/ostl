#pragma once

#include "stage.hpp"
#include "type.hpp"

namespace keros
{
    template<stage, way>
    class scope;

    template<>
    class scope<stage::vertex, way::in>
    {
    public:
        int vertex_index;
    };

    template<>
    class scope<stage::vertex, way::out>
    {
    public:
        vec4 position;
    };
}  // namespace keros