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

        using clock = std::chrono::high_resolution_clock;
        using time_point = clock::time_point;
        [[nodiscard]] time_point now() const;

    private:
        double elapsed();

        time_point m_start_rendering;
        time_point m_finished_rendering;
    };
}  // namespace ostl