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

    std::vector<const char*> glfw_required_extensions()
    {
        std::vector<const char*> required_extensions;
        std::uint32_t count = 0;
        const char** glfw_required_extensions = glfwGetRequiredInstanceExtensions(&count);
        for (const char** index = glfw_required_extensions; index < glfw_required_extensions + count; ++index)
        {
            required_extensions.push_back(*index);
        }
        return required_extensions;
    }
}  // namespace caldera