#pragma once

#include <functional>

#include "../reflect/declaration/shader.hpp"
#include "../reflect/model/utility.hpp"

namespace keros
{
    class context
    {
    public:
        void implement_main(std::function<void()>);

    private:
    };
}  // namespace keros