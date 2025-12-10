#ifndef SDLGAME_SPRITE_
#define SDLGAME_SPRITE_
#include <vector>
#include <set>
#include "math.hpp"
#include "surface.hpp"
namespace sdlgame
{
    /**
     * Should be test heavyly around pointer
     * just use stack-alloc like normal
     * treat the pointer as a address holder only,
     * not an pointer to a heap allocated object
     */
    namespace sprite
    {
        /**
         *
         * The base class for visible game objects.
         * Derived classes will want to override the Sprite.update() and assign a Sprite.image and Sprite.rect attributes.
         * The initializer can accept any number of Group instances to be added to
         *
         */
        class Sprite;
        class Group
        {
        public:
            std::set<Sprite *> sprite_list;
            Group(std::vector<Sprite *> sprites = std::vector<Sprite *>());
            Group &operator=(Group oth);
            std::set<Sprite *> &sprites();
            void add(Sprite *sprite);
            void add(std::vector<Sprite *> &sprites);
            void remove(std::vector<Sprite *> &sprites);
            void remove(Sprite *sprite);
            bool has(std::vector<Sprite *> &sprites);
            bool has(Sprite *sprite);
            void update();
            void draw(sdlgame::surface::Surface &surface);
        };

        class Sprite
        {
        public:
            sdlgame::rect::Rect rect;
            sdlgame::surface::Surface image;
            std::set<Group *> group_list;
            Sprite(std::vector<Group *> groups = std::vector<Group *>());
            /**
             * return a set of group that conrtain this sprite
             */
            std::set<Group *> &groups();
            virtual void update() = 0;
            void add(std::vector<Group *> groups);
            void add(Group *group);
            void remove(std::vector<Group *> groups);
            void remove(Group *group);
            /**
             * remove this sprite from all group, still usable after call
             */
            void kill();
            bool alive();
        };

        /**
         * Also a sprite group, the only difference is it only hold 1 sprite,
         * if you call add, it will replace that sprite
         */
        class GroupSingle
        {
        public:
            Sprite *sprite;
            GroupSingle(Sprite *sprite = NULL);
            void add(Sprite *sprite);
            void remove();
            void update();
            void draw(sdlgame::surface::Surface &surface);
        };

        /**
         * @return a list containing all Sprites in a Group that intersect with another Sprite.
         * Intersection is determined by comparing the Sprite.rect attribute of each Sprite.
         * The dokill argument is a bool. If set to True, all Sprites that collide will be removed from the Group.
         */
        std::vector<Sprite *> spritecollide(Sprite *sprite, Group *group, bool dokill = false);
        /**
         * @return if 2 sprite is collide or not, but using 2 sprite, both must have rect attr defined
         */
        bool collide_rect(Sprite *left, Sprite *right);
        /**
         * Tests for collision between two sprites,
         * by testing to see if two circles centered on the sprites overlap.
         * If the radius value is passed, it will check if 2 circle center at the both rect center is collide with that center and that radius or not
         * otherwise a circle is created that is big enough to completely enclose the sprites rect as given by the "rect" attribute.
         */
        bool collide_circle(Sprite *left, Sprite *right, double left_radius = 0, double right_radius = 0);

    }
}

#endif