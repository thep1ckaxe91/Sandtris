#include "sprite.hpp"
#include "rect.hpp"
#include "surface.hpp"
#include <set>
#include <vector>

namespace sdlgame::sprite {
Group::Group(std::vector<Sprite *> sprites) {
  for (auto sprite : sprites)
    add(sprite);
}
Group &Group::operator=(Group oth) {
  sprite_list = oth.sprite_list;
  return *this;
}

Sprite::Sprite(std::vector<Group *> groups) {
  for (Group *group : groups)
    add(group);
}
/**
 * return a set of group that conrtain this sprite
 */
std::set<Group *> &Sprite::groups() { return group_list; }
void Sprite::add(std::vector<Group *> groups) {
  for (auto &group : groups) {
    group->sprite_list.insert(this);
    group_list.insert(group);
  }
}
void Sprite::add(Group *group) {
  group->sprite_list.insert(this);
  group_list.insert(group);
}
void Sprite::remove(std::vector<Group *> groups) {
  for (auto &group : groups) {
    auto it = group_list.find(group);
    if (it != group_list.end()) {
      group->sprite_list.erase(this);
      group_list.erase(group);
    }
  }
}
void Sprite::remove(Group *group) {
  auto it = group_list.find(group);
  if (it != group_list.end()) {
    group->sprite_list.erase(this);
    group_list.erase(group);
  }
}
/**
 * remove this sprite from all group, still usable after call
 */
void Sprite::kill() {
  for (auto &group : group_list)
    group->sprite_list.erase(this);
  group_list.clear();
}
bool Sprite::alive() { return group_list.size() > 0; }

std::set<Sprite *> &Group::sprites() { return sprite_list; }
void Group::add(Sprite *sprite) {
  sprite_list.insert(sprite);
  sprite->group_list.insert(this);
}
void Group::add(std::vector<Sprite *> &sprites) {
  for (auto &sprite : sprites) {
    sprite_list.insert(sprite);
    sprite->group_list.insert(this);
  }
}
void Group::remove(std::vector<Sprite *> &sprites) {
  for (auto &sprite : sprites) {
    auto it = sprite_list.find(sprite);
    if (it != sprite_list.end()) {
      sprite->remove(this);
      sprite_list.erase(it);
    }
  }
}
void Group::remove(Sprite *sprite) {
  auto it = sprite_list.find(sprite);
  if (it != sprite_list.end()) {
    sprite->remove(this);
    sprite_list.erase(it);
  }
}
bool Group::has(std::vector<Sprite *> &sprites) {
  for (auto &sprite : sprites) {
    if (sprite_list.find(sprite) == sprite_list.end())
      return false;
  }
  return true;
}
bool Group::has(Sprite *sprite) {
  if (sprite_list.find(sprite) == sprite_list.end())
    return false;
  return true;
}
void Group::update() {
  for (auto &sprite : sprite_list) {
    sprite->update();
  }
}
void Group::draw(sdlgame::surface::Surface &surface) {
  for (auto &sprite : sprite_list) {
    surface.blit(*sprite->image, sprite->rect.getTopLeft());
  }
}

GroupSingle::GroupSingle(Sprite *sprite) { sprite = sprite; }
void GroupSingle::add(Sprite *sprite) { sprite = sprite; }
void GroupSingle::remove() { sprite = nullptr; }
void GroupSingle::update() { sprite->update(); }
void GroupSingle::draw(sdlgame::surface::Surface &surface) {
  surface.blit(*sprite->image, sprite->rect.getTopLeft());
}

std::vector<Sprite *> spritecollide(Sprite *sprite, Group *group, bool dokill) {
  std::vector<Sprite *> res;
  for (auto &img : group->sprite_list) {
    if (img->rect.colliderect(sprite->rect)) {
      res.push_back(img);
    }
  }
  if (dokill)
    group->remove(res);
  return res;
}
/**
 * @return if 2 sprite is collide or not, but using 2 sprite, both must have
 * rect attr defined
 */
bool collide_rect(Sprite *left, Sprite *right) {
  return left->rect.colliderect(right->rect);
}
/**
 * Tests for collision between two sprites,
 * by testing to see if two circles centered on the sprites overlap.
 * If the radius value is passed, it will check if 2 circle center at the both
 * rect center is collide with that center and that radius or not otherwise a
 * circle is created that is big enough to completely enclose the sprites rect
 * as given by the "rect" attribute.
 */
bool collide_circle(Sprite *left, Sprite *right, double left_radius,
                    double right_radius) {
  left_radius = (left_radius == 0
                     ? (left->rect.getTopLeft() - left->rect.getBottomRight())
                               .magnitude() /
                           2
                     : left_radius);
  right_radius =
      (right_radius == 0
           ? (right->rect.getTopLeft() - right->rect.getBottomRight())
                     .magnitude() /
                 2
           : right_radius);
  return (left->rect.getCenter() - right->rect.getCenter()).magnitude() <=
         left_radius + right_radius;
}
} // namespace sdlgame::sprite