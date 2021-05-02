#pragma once

#include <chrono>

namespace ostl
{
    class stopwatch
    {
    public:
        void wait_vertical_synchronisation(const int&);
        void start_rendering();
        void finished_rendering();
        double rendering_time();

    private:
        using time_point = std::chrono::steady_clock::time_point;
        time_point now();
        double elapsed();

        time_point m_start_rendering;
        time_point m_finished_rendering;
    };
}  // namespace ostl