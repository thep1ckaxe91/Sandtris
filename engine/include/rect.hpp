#pragma once
#ifndef SDLGAME_RECT_
#define SDLGAME_RECT_
#include "SDL2/SDL_rect.h"
#include "math.hpp"
#include <string>
#include <vector>
#include <optional>

namespace sdlgame::rect {
/**
 *  this is a class represent a Rectangle in SDL2, the coordination
 * in sdl2 is x axis points to the right and y axis points downward
 *
 * Also for pygame user, there's no = and the rect do it for you, you have to
 * use get and set method
 *
 * Though width and height can be negative, it's mostly illegal Rect for most
 * opration, so just dont
 *
 * Most function that have here also have in pygame.Rect, but just some that are
 * most used
 *
 *
 */
class Rect {

private:
  double x, y, w, h;

public:
  Rect() = default;

  Rect(double _left, double _top, double _w, double _h);

  Rect(double _left, double _top, math::Vector2 _size);

  Rect(math::Vector2 pos, double _w, double _h);
  Rect(math::Vector2 pos, math::Vector2 size);

  Rect(const Rect &oth) = default;
  Rect &operator=(const Rect &oth) = default;
  bool operator==(const Rect &oth) const;
  SDL_FRect to_SDL_FRect() const;
  SDL_Rect to_SDL_Rect() const;
  std::string toString() const;

  /**
   * @return a new rectangle that have been moved by given OFFSET x and y
   */
  Rect move(double offset_x, double offset_y) const;

  void move_ip(double offset_x, double offset_y);
  /**
   * @return a new rectangle that have been moved by given OFFSET x and y
   */
  Rect move(math::Vector2 offset) const;
  /**
   *  instead of a new one, this just move the rect that called this function
   */
  void move_ip(math::Vector2 offset);

  /**
   * @return a new rectangle that changed the size to given OFFSET, the topleft
   * of the rectangle is remain still
   */

  Rect inflate(double offset_w, double offset_h) const;
  Rect inflate(math::Vector2 offset) const;
  /**
   *  resize current rectangle with given offset, the topleft of the rectangle
   * is remain still
   */

  void inflate_ip(double offset_w, double offset_h);
  void inflate_ip(const math::Vector2 &offset);

  /**
   *  to update the current rectangle that call the function
   */

  void update(double _left, double _top, double _w, double _h);

  void update(double _left, double _top, math::Vector2 _size);

  void update(math::Vector2 pos, double _w, double _h);
  void update(math::Vector2 pos, math::Vector2 _size);
  /**
   *  return a new rectangle that fit another rect but keep the aspect ratio of
   * the caller the position of the rect that return is the position of the
   * caller
   */
  Rect fit(const Rect &oth) const;
  /**
   * @return return true if the other rect is completely inside the caller
   */
  bool contains(const Rect &oth) const;

  Rect overlap(const Rect &oth) const;
  void overlap_ip(const Rect &oth);

  bool collidepoint(double _x, double _y) const;
  /**
   * @return return whether the point in param is inside the caller or not
   */
  bool collidepoint(const math::Vector2 &point) const;
  /**
   * @return return whether the caller collide with the other rect or not
   */
  bool colliderect(const Rect &oth) const;

  std::optional<std::pair<math::Vector2,math::Vector2>> clipline(const math::Vector2& start, const math::Vector2& end) const;

  /**
   * @return return whether the caller collide with any of the rect in the list
   */
  bool collidelist(std::vector<Rect> &rect_list) const;
  // Under is mostly get and set func

  void setWidth(double _w);

  void setHeight(double _h);

  void setSize(double _w, double _h);
  void setSize(const math::Vector2 &_size);

  void setTop(double _y);

  void setLeft(double _x);

  void setRight(double _x);

  void setBottom(double _y);

  void setTopLeft(double _x, double _y);
  void setTopLeft(const math::Vector2 &pos);

  void setBottomLeft(double _x, double _y);
  void setBottomLeft(const math::Vector2 &pos);

  void setTopRight(double _x, double _y);
  void setTopRight(const math::Vector2 &pos);

  void setBottomRight(double _x, double _y);
  void setBottomRight(const math::Vector2 &pos);

  void setCenter(double _x, double _y);
  void setCenter(math::Vector2 pos);

  void setMidTop(double _x, double _y);
  void setMidTop(const math::Vector2 &pos);

  void setMidBottom(double _x, double _y);
  void setMidBottom(const math::Vector2 &pos);

  void setMidLeft(double _x, double _y);
  void setMidLeft(const math::Vector2 &pos);

  void setMidRight(double _x, double _y);
  void setMidRight(const math::Vector2 &pos);
  double getWidth() const;
  double getHeight() const;
  double getTop() const;
  double getLeft() const;
  double getRight() const;
  double getBottom() const;
  double getCenterX() const;
  double getCenterY() const;
  math::Vector2 getSize() const;
  math::Vector2 getCenter() const;
  math::Vector2 getTopLeft() const;
  math::Vector2 getTopRight() const;
  math::Vector2 getBottomLeft() const;
  math::Vector2 getBottomRight() const;
  math::Vector2 getMidTop() const;
  math::Vector2 getMidLeft() const;
  math::Vector2 getMidBottom() const;
  math::Vector2 getMidRight() const;
};
} // namespace sdlgame::rect

#endif