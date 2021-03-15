#include "caldera/glfw/glfw_utils.hpp"

namespace caldera
{
    glass::keyboard::key glfw_key_convert(int key)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE:
                return glass::keyboard::key::escape;
                break;
            default:
                return glass::keyboard::key::unknown;
        }
    }
}