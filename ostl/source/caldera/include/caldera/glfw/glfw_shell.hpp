#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace ostl
{
    class glfw_shell
    {
    public:
        glfw_shell()
        {
            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
        }

        ~glfw_shell() { glfwTerminate(); }
    };

    static glfw_shell shell;
}  // namespace ostl