#include "ostl/window.hpp"

#include <abacus/abacus.hpp>

namespace ostl
{
    std::string window::hello()
    {
        abacus::vec2 vec2(0, 1);
        return "Hello World !";
    }
}  // namespace ostl