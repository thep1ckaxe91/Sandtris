#include "time.hpp"
#include <thread>
#include <numeric>
namespace sdlgame::time
{

    inline timepoint_t get_ticks()
    {
        return sim_clock_t::now();
    }

    inline void wait(duration_t dur)
    {
        if (dur > duration_t::zero())
        {
            std::this_thread::sleep_for(dur);
        }
    }

    /**
     * Clock object for time manegement in game
     */
    Clock::Clock()
        : last_time(get_ticks()), target_time(get_ticks()), current_elapsed_index(0), bullet_time_multiplier(1)
    {
        elapsed_times.fill(duration_t(1.0 / 60.0));
    }
    /**
     * Update the clock
     * @return the time has passed since the last call to this function
     * @param fps desired FPS, if the fps is too high, it just run as fast as possible
     */
    duration_t Clock::tick(double fps)
    {
        if (fps <= 0.0)
            fps = 1e9;

        auto target_duration = std::chrono::duration_cast<duration_t>(
            std::chrono::duration<double>(1.0 / fps));

        target_time += target_duration;

        auto current_time = get_ticks();
        auto time_to_sleep = target_time - current_time - 2ms; // 2ms buf

        if (time_to_sleep > duration_t::zero())
        {
            std::this_thread::sleep_for(time_to_sleep);
        }

        while (sim_clock_t::now() < target_time)
        {
            std::this_thread::yield();
        }

        timepoint_t capture_now = get_ticks();
        duration_t actual_elapsed = capture_now - last_time;
        last_time = capture_now;

        elapsed_times[current_elapsed_index] = actual_elapsed;
        current_elapsed_index = (current_elapsed_index + 1) % elapsed_times.size();

        return actual_elapsed;
    }

    /**
     * @return delta-time, time passed that calculated from the lastest call to tick() function
     */
    duration_t Clock::delta_time() const
    {
        size_t last_index = (current_elapsed_index == 0)
                                ? elapsed_times.size() - 1
                                : current_elapsed_index - 1;

        return elapsed_times[last_index] * bullet_time_multiplier;
    }
    /**
     * function to set bullet time or slow motion by multiply deltatime with certain percentage,
     * this only work if user use delta_time for movement instead of fixed fps with normal increment
     * @param percentage the value is clamp to [1,100], is how much slower time should
     * flow compare to real-time
     */
    void Clock::set_bullettime_multiplier(double percentage)
    {
        bullet_time_multiplier = (percentage < 1.0 ? 1.0 : (percentage > 100.0 ? 100.0 : percentage)) / 100.0;
    }
    /**
     * @return fps rely on 10 last delta time from tick function
     */
    double Clock::get_fps() const
    {
        duration_t total_time =
            std::accumulate(elapsed_times.begin(), elapsed_times.end(), duration_t::zero());

        double total_seconds = total_time.count();
        if (total_seconds == 0.0)
            return 0.0; // Prevent div by zero

        return static_cast<double>(elapsed_times.size()) / total_seconds;
    }
}