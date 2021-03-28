#pragma once

#include <string>

#include "detail/utility/type.hpp"
#include "logger.hpp"

namespace detail
{
    template<class derived>
    class loggable
    {
    public:
        loggable() : log(create_class_logger(std::string(type_name<derived>()))) {}
        virtual ~loggable() = default;

        mutable logger log;
    };
}  // namespace detail