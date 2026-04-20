#include "sprite.hpp"
#include "rect.hpp"
#include "surface.hpp"
#include <algorithm>
#include <memory>

namespace sdlgame::sprite {

std::span<const std::shared_ptr<Sprite>> Group::sprites() const {
  return m_sprites;
}
void Group::add(const std::shared_ptr<Sprite> &sprite) {
  if (!sprite)
    return;

  auto it = std::ranges::find(m_sprites, sprite);

  if (it == m_sprites.end()) {
    m_sprites.push_back(sprite);

    sprite->m_groups.push_back(weak_from_this());
    sprite->m_cache_dirty = true;
  }
}
void Group::remove(const std::shared_ptr<Sprite> &sprite) {

  if (auto it = std::ranges::find(m_sprites, sprite); it != m_sprites.end()) {
    *it = std::move(m_sprites.back());
    m_sprites.pop_back();

    auto &sprite_groups = sprite->m_groups;

    std::erase_if(sprite_groups, [this](const auto &weak) {
      auto locked = weak.lock();
      return !locked || locked.get() == this;
    });

    sprite->m_cache_dirty = true;
  }
}
bool Group::has(const std::shared_ptr<Sprite> &sprite) const {
  return std::ranges::contains(m_sprites, sprite);
}
void Group::update() {
  for (auto &sprite : m_sprites) {
    sprite->update();
  }
}
void Group::draw(surface::Surface &surface) {
  for (const auto &sprite : m_sprites) {
    surface.blit(*sprite->m_image, sprite->get_rect().getTopLeft(),
                 sprite->get_rect().getSize(), sprite->get_rect());
  }
}

auto Group::begin() const { return m_sprites.begin(); }
auto Group::end() const { return m_sprites.end(); }

Sprite::Sprite(const std::shared_ptr<const surface::Surface> &image)
    : m_image(image), m_rect(image->get_rect()) {}

std::span<const std::shared_ptr<Group>> Sprite::groups() const {
  if (!m_cache_dirty)
    return m_groups_cache;

  m_groups_cache.clear();
  m_groups_cache.reserve(m_groups.size());

  std::erase_if(m_groups, [&](const auto &weak) {
    if (auto shared = weak.lock()) {
      m_groups_cache.push_back(std::move(shared));
      return false;
    }
    return true;
  });

  m_cache_dirty = false;
  return m_groups_cache;
}
void Sprite::add(const std::shared_ptr<Group> &group) {
  group->add(shared_from_this());
}
void Sprite::remove(const std::shared_ptr<Group> &group) {
  group->remove(shared_from_this());
}

void Sprite::kill() {

  for (auto &group : groups()) {
    group->remove(shared_from_this());
  }

  m_groups.clear();
  m_groups_cache.clear();
  m_cache_dirty = false;
}
bool Sprite::alive() const { return !m_groups.empty(); }

rect::Rect &Sprite::get_rect() { return m_rect; }
const rect::Rect &Sprite::get_rect() const { return m_rect; }

const surface::Surface & Sprite::get_image() const {
  return *m_image;
}

GroupSingle::GroupSingle(const std::shared_ptr<Sprite> &sprite) {
  if (sprite)
    this->add(sprite);
}

void GroupSingle::add(const std::shared_ptr<Sprite> &sprite) {
  if (!sprite)
    return;

  if (!m_sprites.empty()) {
    Group::remove(m_sprites.back());
  }

  Group::add(sprite);
}

void GroupSingle::remove() {
  if (!m_sprites.empty())
    Group::remove(m_sprites.back());
}

std::vector<std::shared_ptr<Sprite>>
spritecollide(const std::shared_ptr<Sprite> &sprite,
              const std::shared_ptr<Group> &group, bool dokill) {
  std::vector<std::shared_ptr<Sprite>> res;

  for (const auto &g_sprite : *group) {
    if (collide_rect(*g_sprite, *sprite)) {
      res.push_back(g_sprite);
    }
  }

  if (dokill) {
    for (const auto &r_sprite : res) {
      group->remove(r_sprite);
    }
  }

  return res;
}

bool collide_rect(const Sprite &left, const Sprite &right) {
  return left.get_rect().colliderect(right.get_rect());
}

bool collide_circle(const Sprite &left, const Sprite &right, double left_radius,
                    double right_radius) {
  return left.get_rect().getCenter().distance_to(right.get_rect().getCenter()) <
         left_radius + right_radius;
}

} // namespace sdlgame::sprite
