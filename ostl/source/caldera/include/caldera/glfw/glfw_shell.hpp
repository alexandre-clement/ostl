#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace caldera
{
    class glfw_shell
    {
    public:
        glfw_shell();
        ~glfw_shell();
    };

    static glfw_shell shell;
}  // namespace caldera