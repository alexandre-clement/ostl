#include "caldera/glfw/glfw_shell.hpp"

#include <GLFW/glfw3.h>

namespace caldera
{
    glfw_shell::glfw_shell()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
    }

    glfw_shell::~glfw_shell() { glfwTerminate(); }
}  // namespace caldera