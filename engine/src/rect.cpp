#include "rect.hpp"
#include "SDL2/SDL_rect.h"
#include "math.hpp"
#include <algorithm>
#include <optional>
#include <utility>

namespace sdlgame::rect {

Rect::Rect(double _left, double _top, double _w, double _h)
    : x(_left), y(_top), w(_w), h(_h) {}

Rect::Rect(double _left, double _top, math::Vector2 _size)
    : x(_left), y(_top), w(_size.x), h(_size.y) {}

Rect::Rect(math::Vector2 pos, double _w, double _h)
    : x(pos.x), y(pos.y), w(_w), h(_h) {}
Rect::Rect(math::Vector2 pos, math::Vector2 size)
    : x(pos.x), y(pos.y), w(size.x), h(size.y) {}

bool Rect::operator==(const Rect &oth) const {
  return x == oth.x && y == oth.y && w == oth.w && h == oth.h;
}

SDL_FRect Rect::to_SDL_FRect() const {
  return {static_cast<float>(x), static_cast<float>(y), static_cast<float>(w),
          static_cast<float>(h)};
}

SDL_Rect Rect::to_SDL_Rect() const {
  SDL_Rect res = {
      static_cast<int>(x),
      static_cast<int>(y),
      static_cast<int>(w),
      static_cast<int>(h),
  };
  return res;
}
std::string Rect::toString() const {
  return "Rect<" + std::to_string(x) + "," + std::to_string(y) + "," +
         std::to_string(w) + "," + std::to_string(h) + ">";
}

/**
 * @return a new rectangle that have been moved by given OFFSET x and y
 */
Rect Rect::move(double offset_x, double offset_y) const {
  return {x + offset_x, y + offset_y, w, h};
}

/**
 *  instead of a new one, this just move the rect that called this function
 */
void Rect::move_ip(double offset_x, double offset_y) {
  x += offset_x;
  y += offset_y;
}
/**
 * @return a new rectangle that have been moved by given OFFSET x and y
 */
Rect Rect::move(math::Vector2 offset) const {
  return {offset.x + x, offset.y + y, w, h};
}
/**
 *  instead of a new one, this just move the rect that called this function
 */
void Rect::move_ip(math::Vector2 offset) {
  x += offset.x;
  y += offset.y;
}

/**
 * @return a new rectangle that changed the size to given OFFSET, the topleft of
 * the rectangle is remain still
 */

Rect Rect::inflate(double offset_w, double offset_h) const {
  return {x - offset_w / 2, y - offset_h / 2, w + offset_w, h + offset_h};
}
Rect Rect::inflate(math::Vector2 offset) const {
  return {x - offset.x / 2, y - offset.y / 2, w + offset.x, h + offset.y};
}
/**
 *  resize current rectangle with given offset, the topleft of the rectangle is
 * remain still
 */

void Rect::inflate_ip(double offset_w, double offset_h) {
  x -= offset_w / 2;
  y -= offset_h / 2;
  w += offset_w;
  h += offset_h;
}
void Rect::inflate_ip(const math::Vector2 &offset) {
  x -= offset.x / 2;
  y -= offset.y / 2;
  w += offset.x;
  h += offset.y;
}

/**
 *  to update the current rectangle that call the function
 */
void Rect::update(double _left, double _top, double _w, double _h) {
  *this = {_left, _top, _w, _h};
}

void Rect::update(double _left, double _top, math::Vector2 _size) {
  *this = {_left, _top, _size};
}

void Rect::update(math::Vector2 pos, double _w, double _h) {
  *this = {pos, _w, _h};
}
void Rect::update(math::Vector2 pos, math::Vector2 size) {
  *this = {pos, size};
}
/**
 *  return a new rectangle that fit another rect but keep the aspect ratio of
 * the caller the position of the rect that return is the position of the caller
 */
Rect Rect::fit(const Rect &oth) const {
  Rect res = *this;
  res.setSize(math::Vector2(w, h) * (oth.getWidth() / res.getWidth()));
  return res;
}
/**
 * @return return true if the other rect is completely inside the caller
 */
bool Rect::contains(const Rect &oth) const {
  return x <= oth.x && y <= oth.y && getRight() >= oth.getRight() &&
         getBottom() >= oth.getBottom();
}

Rect Rect::overlap(const Rect &oth) const {
  return (colliderect(oth)
              ? Rect(std::max(x, oth.getLeft()), std::max(y, oth.getTop()),
                     std::min(getRight(), oth.getRight()) -
                         std::max(x, oth.getLeft()),
                     std::min(getBottom(), oth.getBottom()) -
                         std::max(y, oth.getTop()))
              : Rect());
}
void Rect::overlap_ip(const Rect &oth) { *this = overlap(oth); }
/**
 * TEST: approved
 */

bool Rect::collidepoint(double _x, double _y) const {
  return x <= _x && _x <= getRight() && y <= _y && _y <= getBottom();
}
/**
 * @return return whether the point in param is inside the caller or not
 */
bool Rect::collidepoint(const math::Vector2 &point) const {
  return x <= point.x && point.x <= getRight() && y <= point.y &&
         point.y <= getBottom();
}
/**
 * @return return whether the caller collide with the other rect or not
 * TEST: Approved
 */
bool Rect::colliderect(const Rect &oth) const {
  return !(getRight() < oth.x || getBottom() < oth.y || x > oth.getRight() ||
           y > oth.getBottom());
}

// minor attempt for native O3 vectorization
struct alignas(32) Vec4d {
  double values[4];
};

std::optional<std::pair<math::Vector2, math::Vector2>>
Rect::clipline(const math::Vector2 &st, const math::Vector2 &ed) const {
  // liang barsky method
  // 4 ele, left, right, top, bottom acoordingly
  Vec4d q = {st.x - x, x + w - st.x, st.y - y, y + h - st.y};
  Vec4d c = {st.x - ed.x, ed.x - st.x, st.y - ed.y, ed.y - st.y};
  double t0 = 0, t1 = 1;

  for (int i = 0; i < 4; i++) {
    if (c.values[i] == 0.0) {
      if (q.values[i] < 0.0)
        return std::nullopt;
    } else {
      double r = q.values[i] / c.values[i];
      if (c.values[i] > 0)
        t0 = std::max(t0, r);
      else
        t1 = std::min(t1, r);
    }
  }

  if (t0 > t1)
    return std::nullopt;
  return std::pair<math::Vector2, math::Vector2>{
      {st.x + c.values[1] * t0, st.y + c.values[3] * t0},
      {st.x + c.values[1] * t1, st.y + c.values[3] * t1}};
}

/**
 * @return return whether the caller collide with any of the rect in the list
 */
bool Rect::collidelist(std::vector<Rect> &rect_list) const {
  for (Rect &rect : rect_list)
    if (colliderect(rect))
      return true;
  return false;
}

// Under is mostly get and set func

void Rect::setWidth(double _w) { inflate_ip(_w - w, 0); }

void Rect::setHeight(double _h) { inflate_ip(0, _h - h); }

void Rect::setSize(double _w, double _h) { inflate_ip(_w - w, _h - h); }
void Rect::setSize(const math::Vector2 &_size) {
  inflate_ip(_size - math::Vector2(w, h));
}

void Rect::setTop(double _y) {
  // std::cout << "Moved the rect by " << _y - y << " in y axis\n";
  move_ip(0, _y - y);
}

void Rect::setLeft(double _x) {
  // std::cout << "Moved the rect by " << _x - x << " in x axis\n";
  move_ip(_x - x, 0);
}

void Rect::setRight(double _x) {
  // std::cout << "Moved the rect by " << _x - x << " in x axis\n";
  move_ip(_x - getRight(), 0);
}

void Rect::setBottom(double _y) {
  // std::cout << "Moved the rect by " << _y - y << " in y axis\n";
  move_ip(0, _y - getBottom());
}

void Rect::setTopLeft(double _x, double _y) { move_ip(_x - x, _y - y); }
void Rect::setBottomLeft(double _x, double _y) {
  move_ip(_x - x, _y - getBottom());
}
void Rect::setTopRight(double _x, double _y) {
  move_ip(_x - getRight(), _y - y);
}
void Rect::setBottomRight(double _x, double _y) {
  move_ip(_x - getRight(), _y - getBottom());
}

void Rect::setTopLeft(const math::Vector2 &pos) { move_ip(pos - getTopLeft()); }
void Rect::setBottomLeft(const math::Vector2 &pos) {
  move_ip(pos - getBottomLeft());
}
void Rect::setTopRight(const math::Vector2 &pos) {
  move_ip(pos - getTopRight());
}
void Rect::setBottomRight(const math::Vector2 &pos) {
  move_ip(pos - getBottomRight());
}
void Rect::setCenter(double _x, double _y) {
  move_ip(_x - getCenterX(), _y - getCenterY());
}
void Rect::setCenter(math::Vector2 pos) {
  move_ip(pos.x - getCenterX(), pos.y - getCenterY());
}

void Rect::setMidTop(double _x, double _y) {
  move_ip(_x - getCenterX(), _y - y);
}
void Rect::setMidTop(const math::Vector2 &pos) {
  move_ip(pos.x - getCenterX(), pos.y - y);
}

void Rect::setMidBottom(double _x, double _y) {
  move_ip(_x - getCenterX(), _y - getBottom());
}
void Rect::setMidBottom(const math::Vector2 &pos) {
  move_ip(pos.x - getCenterX(), pos.y - getBottom());
}

void Rect::setMidLeft(double _x, double _y) {
  move_ip(_x - x, _y - getCenterY());
}
void Rect::setMidLeft(const math::Vector2 &pos) {
  move_ip(pos.x - x, pos.y - getCenterY());
}

void Rect::setMidRight(double _x, double _y) {
  move_ip(_x - getRight(), _y - getCenterY());
}
void Rect::setMidRight(const math::Vector2 &pos) {
  move_ip(pos.x - getRight(), pos.y - getCenterY());
}
double Rect::getWidth() const { return w; }
double Rect::getHeight() const { return h; }
double Rect::getTop() const { return y; }
double Rect::getLeft() const { return x; }
double Rect::getRight() const { return x + w; }
double Rect::getBottom() const { return y + h; }
double Rect::getCenterX() const { return x + w / 2; }
double Rect::getCenterY() const { return y + w / 2; }
math::Vector2 Rect::getSize() const { return {w, h}; }
math::Vector2 Rect::getCenter() const { return {getCenterX(), getCenterY()}; }
math::Vector2 Rect::getTopLeft() const { return {x, y}; }
math::Vector2 Rect::getTopRight() const { return {y, getRight()}; }
math::Vector2 Rect::getBottomLeft() const { return {getBottom(), x}; }
math::Vector2 Rect::getBottomRight() const { return {getBottom(), getRight()}; }
math::Vector2 Rect::getMidTop() const { return {getCenterX(), y}; }
math::Vector2 Rect::getMidLeft() const { return {x, getCenterY()}; }
math::Vector2 Rect::getMidBottom() const { return {getCenterX(), getBottom()}; }
math::Vector2 Rect::getMidRight() const { return {getRight(), getCenterY()}; }

} // namespace sdlgame::rect