#pragma once
#ifndef SDLGAME_RECT_
#define SDLGAME_RECT_
#include "math.hpp"
#include "SDL2/SDL.h"
#include <vector>
#include <string>

namespace sdlgame
{
    /// @brief namespace for rect usage
    namespace rect
    {
        /**
         *  this is a class represent a Rectangle in SDL2, the coordination
         * in sdl2 is x axis points to the right and y axis points downward
         * it's a little unintuitive, but you'll sure have the hang of it and why it should be like that
         *
         * Also for pygame user, there's no = and the rect do it for you, you have to use get and set method,
         * otherwise, ready for immense amount of bug.
         *
         * Though width and height can be negative, it's mostly illegal Rect for most opration, so just dont
         *
         * Most function that have here also have in pygame.Rect, but just some that are most used
         *
         * 
         */
        class Rect
        {

        private:
            double x, y, left, top, bottom, right;
            double w, h, width, height;
            double centerx, centery;
            // sdlgame::math::Vector2 center, topleft, bottomleft, topright, bottomright, midtop, midleft, midbottom, midright;
            // sdlgame::math::Vector2 size;

        public:
            Rect();
            
            Rect(double _left, double _top, double _w, double _h);
            
            Rect(double _left, double _top, sdlgame::math::Vector2 _size);
            
            Rect(sdlgame::math::Vector2 pos, double _w, double _h);
            Rect(sdlgame::math::Vector2 pos, sdlgame::math::Vector2 size);
            /**
             * @return a new rectangle that have been moved by given OFFSET x and y
             */
            Rect &operator=(Rect oth);
            bool operator==(const Rect &oth) const;
            SDL_FRect to_SDL_FRect() const;
            /**
             * TEST: Approved
             */
            
            Rect move(double offset_x, double offset_y) const;

            /**
             *  instead of a new one, this just move the rect that called this function
             * TEST: Approved
             */
            
            void move_ip(double offset_x, double offset_y);
            /**
             * @return a new rectangle that have been moved by given OFFSET x and y
             */
            Rect move(sdlgame::math::Vector2 offset) const;
            /**
             *  instead of a new one, this just move the rect that called this function
             */
            void move_ip(sdlgame::math::Vector2 offset);

            /**
             * @return a new rectangle that changed the size to given OFFSET, the topleft of the rectangle is remain still
             */
            
            Rect inflate(double offset_w, double offset_h) const;
            Rect inflate(sdlgame::math::Vector2 offset) const;
            /**
             *  resize current rectangle with given offset, the topleft of the rectangle is remain still
             */
            
            void inflate_ip(double offset_w, double offset_h);
            void inflate_ip(const sdlgame::math::Vector2 &offset);

            /**
             *  to update the current rectangle that call the function
             */
            
            void update(double _left, double _top, double _w, double _h);
            
            void update(double _left, double _top, sdlgame::math::Vector2 _size);
            
            void update(sdlgame::math::Vector2 pos, double _w, double _h);
            void update(sdlgame::math::Vector2 pos, sdlgame::math::Vector2 _size);
            /**
             *  return a new rectangle that fit another rect but keep the aspect ratio of the caller
             * the position of the rect that return is the position of the caller
             */
            Rect fit(const Rect oth) const;
            /**
             * @return return true if the other rect is completely inside the caller
             */
            bool contains(const Rect oth) const;

            Rect overlap(const Rect& oth);
            void overlap_ip(const Rect& oth);
            /**
             * TEST: approved
             */
            
            bool collidepoint(double _x, double _y) const;
            /**
             * @return return whether the point in param is inside the caller or not
             */
            bool collidepoint(const sdlgame::math::Vector2 point);
            /**
             * @return return whether the caller collide with the other rect or not
             * TEST: Approved
             */
            bool colliderect(const Rect oth) const;

            // bool collideline(const Vector2 start, const Vector2 end)
            // {
            //     double t = ((end.x - start.x) * (y - start.y) - (end.y - start.y) * (x - start.x)) / ((end.x - start.x) * (y + h - start.y) - (end.y - start.y) * (x + w - start.x));
            //     double u = ((x - start.x) * (end.y - start.y) - (y - start.y) * (end.x - start.x)) / ((end.x - start.x) * (y + h - start.y) - (end.y - start.y) * (x + w - start.x));
                
            
            // }
            /**
             * @return return whether the caller collide with any of the rect in the list
             */
            bool collidelist(std::vector<Rect> &rect_list) const;
            // Under is mostly get and set func
            
            void setWidth(double _w);
            
            void setHeight(double _h);
            
            void setSize(double _w, double _h);
            void setSize(const sdlgame::math::Vector2 &_size);
            
            void setTop(double _y);
            
            void setLeft(double _x);
            
            void setRight(double _x);
            
            void setBottom(double _y);
            
            void setTopLeft(double _x, double _y);
            void setTopLeft(const sdlgame::math::Vector2 &pos);

            void setBottomLeft(double _x, double _y);
            void setBottomLeft(const sdlgame::math::Vector2 &pos);

            void setTopRight(double _x, double _y);
            void setTopRight(const sdlgame::math::Vector2 &pos);
            
            void setBottomRight(double _x, double _y);
            void setBottomRight(const sdlgame::math::Vector2 &pos);

            void setCenter(double _x, double _y);
            void setCenter(sdlgame::math::Vector2 pos);
            
            void setMidTop(double _x, double _y);
            void setMidTop(const sdlgame::math::Vector2 &pos);
            
            void setMidBottom(double _x, double _y);
            void setMidBottom(const sdlgame::math::Vector2 &pos);
            
            void setMidLeft(double _x, double _y);
            void setMidLeft(const sdlgame::math::Vector2 &pos);
            
            void setMidRight(double _x, double _y);
            void setMidRight(const sdlgame::math::Vector2 &pos);
            double getWidth() const;
            double getHeight() const;
            double getTop() const;
            double getLeft() const;
            double getRight() const;
            double getBottom() const;
            double getCenterX() const;
            double getCenterY() const;
            sdlgame::math::Vector2 getSize() const;
            sdlgame::math::Vector2 getCenter() const;
            sdlgame::math::Vector2 getTopLeft() const;
            sdlgame::math::Vector2 getTopRight() const;
            sdlgame::math::Vector2 getBottomLeft() const;
            sdlgame::math::Vector2 getBottomRight() const;
            sdlgame::math::Vector2 getMidTop() const;
            sdlgame::math::Vector2 getMidLeft() const;
            sdlgame::math::Vector2 getMidBottom() const;
            sdlgame::math::Vector2 getMidRight() const;

            /**
             *  return a SDL_Rect object from this rect
             */
            SDL_Rect to_SDL_Rect() const;
            std::string toString() const;
        };
    }
}


#endif