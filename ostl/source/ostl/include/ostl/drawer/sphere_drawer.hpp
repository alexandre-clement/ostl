#pragma once

#include "../drawer.hpp"
#include "../object/sphere.hpp"
#include "../texture.hpp"

namespace ostl
{
    template<>
    class drawer<sphere>
    {
    public:
        static void draw(sphere s, texture t) {}
    };
}  // namespace ostl