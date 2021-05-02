#pragma once

#include "stage.hpp"
#include "type.hpp"

namespace keros
{
    template<stage t, way io>
    class scope;

    template<>
    class scope<stage::vertex, way::in>
    {
    public:
        int gl_vertex_index;
    };

    template<>
    class scope<stage::vertex, way::out>
    {
    public:
        vec4 gl_position;
    };
}  // namespace keros