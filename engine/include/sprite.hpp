#ifndef SDLGAME_SPRITE_
#define SDLGAME_SPRITE_
#include "rect.hpp"
#include "surface.hpp"
#include <memory>
#include <span>
#include <vector>

// TODO: there are serveral ideas that might be helful in the future, includes:
// + add with Container iterator begin and end with template
// + more proper inheritance design

namespace sdlgame::sprite {

class Sprite;

class Group : public std::enable_shared_from_this<Group> {

protected:
  std::vector<std::shared_ptr<Sprite>> m_sprites;

public:
  Group() = default;
  virtual ~Group() = default;

  std::span<const std::shared_ptr<Sprite>> sprites() const;
  virtual void add(const std::shared_ptr<Sprite> &sprite);
  virtual void remove(const std::shared_ptr<Sprite> &sprite);
  bool has(const std::shared_ptr<Sprite> &sprite) const;
  virtual void update();
  virtual void draw(surface::Surface &surface);

  auto begin() const;
  auto end() const;
};

class Sprite : public std::enable_shared_from_this<Sprite> {
  friend class Group;
  friend class GroupSingle;

protected:
  rect::Rect m_rect;
  std::shared_ptr<const surface::Surface> m_image;

  mutable std::vector<std::weak_ptr<Group>> m_groups;
  mutable std::vector<std::shared_ptr<Group>> m_groups_cache;
  mutable bool m_cache_dirty = true;

public:
  Sprite() = default;
  explicit Sprite(const std::shared_ptr<const surface::Surface> &image);

  Sprite(const Sprite &) = delete;
  Sprite(Sprite &&) = delete;
  Sprite &operator=(const Sprite &) = delete;
  Sprite &operator=(Sprite &&) = delete;

  virtual ~Sprite();

  std::span<const std::shared_ptr<Group>> groups() const;
  virtual void update() = 0;
  void add(const std::shared_ptr<Group> &group);
  void remove(const std::shared_ptr<Group> &group);

  /**
   * remove this sprite from all group, still usable after call
   */
  void kill();
  bool alive() const;

  rect::Rect &get_rect();
  const rect::Rect &get_rect() const;

  const surface::Surface & get_image() const;
};

/**
 * Also a sprite group, the only difference is it only hold 1 sprite,
 * if you call add, it will replace that sprite
 */
class GroupSingle : public Group {
public:
  explicit GroupSingle(const std::shared_ptr<Sprite> &sprite = nullptr);
  void add(const std::shared_ptr<Sprite> &sprite) override;
  void remove();
  using Group::remove;
};

/**
 * @return a list containing all Sprites in a Group that intersect with another
 * Sprite. Intersection is determined by comparing the Sprite.rect attribute of
 * each Sprite. The dokill argument is a bool. If set to True, all Sprites that
 * collide will be removed from the Group.
 */
std::vector<std::shared_ptr<Sprite>>
spritecollide(const std::shared_ptr<Sprite> &sprite,
              const std::shared_ptr<Group> &group, bool dokill = false);

/**
 * @return if 2 sprite is collide or not, but using 2 sprite, both must have
 * rect attr defined
 */
bool collide_rect(const Sprite &left, const Sprite &right);

/**
 * Tests for collision between two sprites,
 * by testing to see if two circles centered on the sprites overlap.
 * If the radius value is passed, it will check if 2 circle center at the both
 * rect center is collide with that center and that radius or not otherwise a
 * circle is created that is big enough to completely enclose the sprites rect
 * as given by the "rect" attribute.
 */
bool collide_circle(const Sprite &left, const Sprite &right,
                    double left_radius = 0, double right_radius = 0);

} // namespace sdlgame::sprite

#endif
