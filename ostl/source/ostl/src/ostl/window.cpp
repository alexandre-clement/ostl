#include "ostl/window.hpp"

#include <heron/heron.hpp>

namespace ostl
{
    std::string window::hello()
    {
        heron::vec2 vec2(0, 1);
        return "Hello World !";
    }
}  // namespace ostl