#ifndef SDLGAME_TIME_
#define SDLGAME_TIME_
#include <list>
#include "SDL2/SDL.h"
namespace sdlgame
{
    namespace time
    {
        /**
         * @return get time from init in milisecond
         */
        Uint64 get_ticks();
        /**
         * get time from init in milisecond
         */
        void wait(Uint32 miliseconds);

        /**
         * Clock object for time manegement in game
         */
        class Clock
        {
        private:
            Uint32 time;
            std::list<Uint32> elapsedTimes;
            int MAX_FPS;
            double bullet_time_multiplier;

        public:
            Clock();
            /**
             * Update the clock
             * @return the time has passed since the last call to this function
             * @param fps desired FPS, if the fps is too high, it just run as fast as possible
             */
            Uint32 tick(double fps = 0);

            /**
             * @return delta-time, time passed that calculated from the lastest call to tick() function
             */
            double delta_time() const;
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

    }
} // namespace sdlgame


#endif