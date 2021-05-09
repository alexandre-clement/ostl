#include "ostl/stopwatch.hpp"

namespace ostl
{
    void stopwatch::wait_vertical_synchronisation(const int& p_refresh_rate)
    {
        while (elapsed() + rendering_time() < 1. / p_refresh_rate)
            ;
    }

    void stopwatch::start_rendering() { m_start_rendering = now(); }

    void stopwatch::finished_rendering() { m_finished_rendering = now(); }

    double stopwatch::rendering_time()
    {
        return std::chrono::duration<double, std::chrono::seconds::period>(m_finished_rendering - m_start_rendering).count();
    }

    stopwatch::time_point stopwatch::now() const { return clock::now(); }

    double stopwatch::elapsed()
    {
        return std::chrono::duration<double, std::chrono::seconds::period>(now() - m_finished_rendering).count();
    }
}  // namespace ostl