#pragma once
#ifndef SDLGAME_TIME_
#define SDLGAME_TIME_
#include <chrono>
#include <array>
#include <stdfloat>
#include <unordered_map>
#include "SDL2/SDL.h"

using namespace std::literals;
struct SimClock
{
    using rep = std::float64_t;   // sub precision
    using period = std::ratio<1>; // 1:1 with sec
    using duration = std::chrono::duration<rep, period>;
    using time_point = std::chrono::time_point<SimClock>;
    static constexpr bool is_steady = true;

    static time_point now() noexcept
    {
        using namespace std::chrono;
        auto steady_now = steady_clock::now();
        auto duration_in_double = duration_cast<duration>(steady_now.time_since_epoch());
        return time_point{duration_in_double};
    }
};

// since we only use this namespace for measurement and benchmark, datetime related should be a different namespace
using sim_clock_t = SimClock;
using duration_t = SimClock::duration;
using timepoint_t = SimClock::time_point;

namespace sdlgame::time
{

    /**
     * @return get time from init in milisecond
     */
    inline timepoint_t get_ticks();

    /**
     * Sleep with duration, not a busy loop
     */
    inline void wait(duration_t);

    /**
     * Clock object for time manegement in game
     */
    class Clock
    {
    private:
        std::array<duration_t, 10> elapsed_times;
        timepoint_t last_time;
        timepoint_t target_time;
        size_t current_elapsed_index;
        double bullet_time_multiplier;

    public:
        Clock();
        /**
         * Update the clock
         * @return the time has passed since the last call to this function
         * @param fps desired FPS, if the fps is too high, it just run as fast as possible
         */
        duration_t tick(double fps = 0);

        /**
         * @return delta-time, time passed that calculated from the lastest call to tick() function
         */
        duration_t delta_time() const;
        /**
         * function to set bullet time or slow motion by multiply deltatime with certain percentage,
         * this only work if user use delta_time for movement instead of fixed fps with normal increment
         * @param percentage the value is clamp to [1,100], is how much slower time should
         * flow compare to real-time
         */
        void set_bullettime_multiplier(double percentage);
        /**
         * @return fps rely on 10 last delta time from tick function
         */
        double get_fps() const;
    };

    struct FunctionStats
    {
        duration_t total_time;
        duration_t min_time;
        duration_t max_time;
        size_t call_count;

        duration_t avg_time() const;
    };

    /**
     * To gather concise info about a timed function, we will need a TimerManager act as a "observer" to Timers
     * TimerManager will be global anyway, so might as well make it singleton
     */
    class TimerManager
    {
        std::unordered_map<std::string, FunctionStats> functions_stats;
        TimerManager();

    public:
        TimerManager(const TimerManager &) = delete;
        void operator=(const TimerManager &) = delete;
        static TimerManager &instance();
        FunctionStats &get_stat(const std::string &name);
        void report(const std::string &name, duration_t dur);
        std::unordered_map<std::string, FunctionStats> &get_all();
    };

    class Timer
    {
        std::string name;
        timepoint_t start;

    public:
        Timer(const std::string &name = "Func");
        Timer(const char *name = "Func");
        Timer(std::string &&name);

        ~Timer();
    };

}
#endif