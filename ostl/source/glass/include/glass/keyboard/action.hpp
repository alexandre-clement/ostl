#pragma once

namespace glass::keyboard
{
    enum class action
    {
        unknown = -1,

        press = 0,
        hold,
        release,

        count
    };
}  // namespace glass::keyboard
