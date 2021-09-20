#pragma once

#include <functional>

namespace keros
{
    class context
    {
    public:
        void implement_main(std::function<void()>) {}
    };
}  // namespace keros