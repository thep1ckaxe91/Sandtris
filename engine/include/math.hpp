#pragma once
#ifndef SDLGAME_MATH_
#define SDLGAME_MATH_
#include <cmath>
#include "SDL2/SDL.h"
#include <string>
namespace sdlgame {
    /**
     * namespace for most use math functionality in game dev
     */
    namespace math
    {
        double degree_to_radian(double deg);
        double radian_to_degree(double rad);
        double clamp(double val, double left,double right);
        /**
         *  a class for 2D vector, also can represent a point on a 2d surface
         * since the simplicity of 2d vector, we dont need get and set function
         *
         * also for some dumb reason, you can do Vector2 * number, but not number * Vector2
         *
         */
        class Vector2
        {
        public:
            double x, y;
            Vector2();
            Vector2(const SDL_Point &p);
            Vector2(const Vector2 &oth);
            Vector2(double _x, double _y);
            Vector2 &operator=(const Vector2 &oth);
            sdlgame::math::Vector2 &operator+=(const sdlgame::math::Vector2 &oth);
            sdlgame::math::Vector2 &operator-=(const sdlgame::math::Vector2 &oth);
            sdlgame::math::Vector2 &operator*=(const double &scalar);
            sdlgame::math::Vector2 operator+(const sdlgame::math::Vector2 &oth) const;
            sdlgame::math::Vector2 operator-() const;
            sdlgame::math::Vector2 operator-(const sdlgame::math::Vector2 &oth) const;
            sdlgame::math::Vector2 operator*(const double &scalar) const;

            bool operator==(const sdlgame::math::Vector2 &oth) const;
            /**
             * @return length of the vector
             */
            double magnitude() const;
            /**
             * @return the squared value of the length of the vector
             */
            double sqr_magnitude() const;
            /**
             * @return a normalized vector (a vector with length 1 unit) that have the same direction with the original
             */
            sdlgame::math::Vector2 normalize() const;
            /**
             *  normalize the vector
             */
            void normalize_ip();
            /**
             * @return dot product between 2 vector
             */
            double dot(const sdlgame::math::Vector2 &oth) const;
            /**
             * @return angle in degree to another vector in range [0,180] degrees, which is the smallest of 2 angle
             * */
            double angle_to(const sdlgame::math::Vector2 &oth) const;

            /**
             * @return a vector that rotated deg degrees counter clockwise
             * */
            sdlgame::math::Vector2 rotate(double deg) const;
            /**
             *  make the vector rotate deg degrees counter-clockwise
             */
            void rotate_ip(double deg);
            /**
             * @return distance between 2 point
             */
            double distance_to(const sdlgame::math::Vector2 &oth) const;
            /**
             * @return the vector that is the reflection of the current vector to a normal vector
             */
            sdlgame::math::Vector2 reflect(const sdlgame::math::Vector2 &normal) const;
            /**
             * reflect the vector through a normal vector
             */
            void reflect_ip(const sdlgame::math::Vector2 &normal);
            /**
             * @return a projected vector from this vector to a normal vector
             */
            sdlgame::math::Vector2 project(const sdlgame::math::Vector2 &normal) const;
            /**
             * project the vector onto a normal vector
             */
            void project_ip(const sdlgame::math::Vector2 &normal);
            std::string toString() const;
            SDL_FPoint to_SDL_FPoint() const;
        };

        sdlgame::math::Vector2 operator*(const double &scalar, const sdlgame::math::Vector2 &v);
    }
}

#endif