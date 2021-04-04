#include "caldera/glfw/glfw_utils.hpp"

#include <GLFW/glfw3.h>

namespace caldera
{
    glass::keyboard::key glfw_key_convert(int key)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE:
                return glass::keyboard::key::escape;
                break;
            case GLFW_KEY_F11:
                return glass::keyboard::key::f11;
                break;
            default:
                return glass::keyboard::key::unknown;
        }
    }
}  // namespace caldera