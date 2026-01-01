#include "rect.hpp"
#include "surface.hpp"
#include <set>
#include <vector>
#include "sprite.hpp"

sdlgame::sprite::Group::Group(std::vector<Sprite *> sprites)
{
    for (auto sprite : sprites)
        this->add(sprite);
}
sdlgame::sprite::Group &sdlgame::sprite::Group::operator=(Group oth)
{
    sprite_list = oth.sprite_list;
    return *this;
}

sdlgame::sprite::Sprite::Sprite(std::vector<Group *> groups)
{
    for (Group *group : groups)
        this->add(group);
}
/**
 * return a set of group that conrtain this sprite
 */
std::set<sdlgame::sprite::Group *> &sdlgame::sprite::Sprite::groups()
{
    return group_list;
}
void sdlgame::sprite::Sprite::add(std::vector<Group *> groups)
{
    for (auto &group : groups)
    {
        group->sprite_list.insert(this);
        group_list.insert(group);
    }
}
void sdlgame::sprite::Sprite::add(Group *group)
{
    group->sprite_list.insert(this);
    group_list.insert(group);
}
void sdlgame::sprite::Sprite::remove(std::vector<Group *> groups)
{
    for (auto &group : groups)
    {
        auto it = group_list.find(group);
        if (it != group_list.end())
        {
            group->sprite_list.erase(this);
            group_list.erase(group);
        }
    }
}
void sdlgame::sprite::Sprite::remove(Group *group)
{
    auto it = group_list.find(group);
    if (it != group_list.end())
    {
        group->sprite_list.erase(this);
        group_list.erase(group);
    }
}
/**
 * remove this sprite from all group, still usable after call
 */
void sdlgame::sprite::Sprite::kill()
{
    for (auto &group : group_list)
        group->sprite_list.erase(this);
    group_list.clear();
}
bool sdlgame::sprite::Sprite::alive()
{
    return group_list.size() > 0;
}

std::set<sdlgame::sprite::Sprite *> &sdlgame::sprite::Group::sprites()
{
    return sprite_list;
}
void sdlgame::sprite::Group::add(Sprite *sprite)
{
    sprite_list.insert(sprite);
    sprite->group_list.insert(this);
}
void sdlgame::sprite::Group::add(std::vector<Sprite *> &sprites)
{
    for (auto &sprite : sprites)
    {
        sprite_list.insert(sprite);
        sprite->group_list.insert(this);
    }
}
void sdlgame::sprite::Group::remove(std::vector<Sprite *> &sprites)
{
    for (auto &sprite : sprites)
    {
        auto it = sprite_list.find(sprite);
        if (it != sprite_list.end())
        {
            sprite->remove(this);
            sprite_list.erase(it);
        }
    }
}
void sdlgame::sprite::Group::remove(Sprite *sprite)
{
    auto it = sprite_list.find(sprite);
    if (it != sprite_list.end())
    {
        sprite->remove(this);
        sprite_list.erase(it);
    }
}
bool sdlgame::sprite::Group::has(std::vector<Sprite *> &sprites)
{
    for (auto &sprite : sprites)
    {
        if (sprite_list.find(sprite) == sprite_list.end())
            return false;
    }
    return true;
}
bool sdlgame::sprite::Group::has(Sprite *sprite)
{
    if (sprite_list.find(sprite) == sprite_list.end())
        return false;
    return true;
}
void sdlgame::sprite::Group::update()
{
    for (auto &sprite : sprite_list)
    {
        sprite->update();
    }
}
void sdlgame::sprite::Group::draw(sdlgame::surface::Surface &surface)
{
    for (auto &sprite : sprite_list)
    {
        surface.blit(sprite->image, sprite->rect.getTopLeft());
    }
}

sdlgame::sprite::GroupSingle::GroupSingle(Sprite *sprite)
{
    this->sprite = sprite;
}
void sdlgame::sprite::GroupSingle::add(Sprite *sprite)
{
    this->sprite = sprite;
}
void sdlgame::sprite::GroupSingle::remove()
{
    sprite = NULL;
}
void sdlgame::sprite::GroupSingle::update()
{
    sprite->update();
}
void sdlgame::sprite::GroupSingle::draw(sdlgame::surface::Surface &surface)
{
    surface.blit(sprite->image, sprite->rect.getTopLeft());
}

std::vector<sdlgame::sprite::Sprite *> spritecollide(sdlgame::sprite::Sprite *sprite, sdlgame::sprite::Group *group, bool dokill)
{
    std::vector<sdlgame::sprite::Sprite *> res;
    for (auto &img : group->sprite_list)
    {
        if (img->rect.colliderect(sprite->rect))
        {
            res.push_back(img);
        }
    }
    if (dokill)
        group->remove(res);
    return res;
}
/**
 * @return if 2 sprite is collide or not, but using 2 sprite, both must have rect attr defined
 */
bool sdlgame::sprite::collide_rect(sdlgame::sprite::Sprite *left, sdlgame::sprite::Sprite *right)
{
    return left->rect.colliderect(right->rect);
}
/**
 * Tests for collision between two sprites,
 * by testing to see if two circles centered on the sprites overlap.
 * If the radius value is passed, it will check if 2 circle center at the both rect center is collide with that center and that radius or not
 * otherwise a circle is created that is big enough to completely enclose the sprites rect as given by the "rect" attribute.
 */
bool sdlgame::sprite::collide_circle(sdlgame::sprite::Sprite *left,sdlgame::sprite::Sprite *right, double left_radius, double right_radius)
{
    left_radius = (left_radius == 0 ? (left->rect.getTopLeft() - left->rect.getBottomRight()).magnitude() / 2 : left_radius);
    right_radius = (right_radius == 0 ? (right->rect.getTopLeft() - right->rect.getBottomRight()).magnitude() / 2 : right_radius);
    return (left->rect.getCenter() - right->rect.getCenter()).magnitude() <= left_radius + right_radius;
}
