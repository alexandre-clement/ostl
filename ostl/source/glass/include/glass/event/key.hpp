#pragma once

namespace glass::event
{
    enum class key
    {
        unknown = -1,
        escape = 0,

        count
    };

    enum class action
    {
        unknown,
        press,
        hold,
        release,

        count
    };
}  // namespace glass::event