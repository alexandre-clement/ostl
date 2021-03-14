#include "ostl/texture/no_texture.hpp"

namespace ostl
{
    texture no_texture()
    {
        return [](ray_hit) { return vec4(); };
    }
}  // namespace ostl