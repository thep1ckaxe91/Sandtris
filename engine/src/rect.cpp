#include "rect.hpp"
#include "SDL2/SDL_rect.h"

namespace sdlgame::rect {

Rect::Rect() {
  x = y = left = top = bottom = right = w = h = width = height = centerx =
      centery = 0;
}

Rect::Rect(double _left, double _top, double _w, double _h) {
  x = left = _left;
  y = top = _top;
  w = width = _w;
  h = height = _h;
  bottom = top + h;
  right = left + w;
  // size = sdlgame::math::Vector2(w, h);
  centerx = x + width / 2;
  centery = y + height / 2;
  // center = sdlgame::math::Vector2(centerx, centery);
  // topleft = sdlgame::math::Vector2(left, top);
  // bottomleft = sdlgame::math::Vector2(left, bottom);
  // bottomright = sdlgame::math::Vector2(right, bottom);
  // topright = sdlgame::math::Vector2(right, top);
  // midtop = sdlgame::math::Vector2(centerx, top);
  // midleft = sdlgame::math::Vector2(left, centery);
  // midbottom = sdlgame::math::Vector2(centerx, bottom);
  // midright = sdlgame::math::Vector2(right, centery);
}

Rect::Rect(double _left, double _top, sdlgame::math::Vector2 _size) {
  x = left = _left;
  y = top = _top;
  w = width = _size.x;
  h = height = _size.y;
  bottom = top + h;
  right = left + w;
  // size = _size;
  centerx = x + width / 2;
  centery = y + height / 2;
  // center = sdlgame::math::Vector2(centerx, centery);
  // topleft = sdlgame::math::Vector2(left, top);
  // bottomleft = sdlgame::math::Vector2(left, bottom);
  // bottomright = sdlgame::math::Vector2(right, bottom);
  // topright = sdlgame::math::Vector2(right, top);
  // midtop = sdlgame::math::Vector2(centerx, top);
  // midleft = sdlgame::math::Vector2(left, centery);
  // midbottom = sdlgame::math::Vector2(centerx, bottom);
  // midright = sdlgame::math::Vector2(right, centery);
}

Rect::Rect(sdlgame::math::Vector2 pos, double _w, double _h) {
  x = left = pos.x;
  y = top = pos.y;
  w = width = _w;
  h = height = _h;
  bottom = top + h;
  right = left + w;
  // size = sdlgame::math::Vector2(w, h);
  centerx = x + width / 2;
  centery = y + height / 2;
  // center = sdlgame::math::Vector2(centerx, centery);
  // topleft = sdlgame::math::Vector2(left, top);
  // bottomleft = sdlgame::math::Vector2(left, bottom);
  // bottomright = sdlgame::math::Vector2(right, bottom);
  // topright = sdlgame::math::Vector2(right, top);
  // midtop = sdlgame::math::Vector2(centerx, top);
  // midleft = sdlgame::math::Vector2(left, centery);
  // midbottom = sdlgame::math::Vector2(centerx, bottom);
  // midright = sdlgame::math::Vector2(right, centery);
}
Rect::Rect(sdlgame::math::Vector2 pos, sdlgame::math::Vector2 size) {
  x = left = pos.x;
  y = top = pos.y;
  w = width = size.x;
  h = height = size.y;
  bottom = top + h;
  right = left + w;
  // size = _size;
  centerx = x + width / 2;
  centery = y + height / 2;
  // center = sdlgame::math::Vector2(centerx, centery);
  // topleft = sdlgame::math::Vector2(left, top);
  // bottomleft = sdlgame::math::Vector2(left, bottom);
  // bottomright = sdlgame::math::Vector2(right, bottom);
  // topright = sdlgame::math::Vector2(right, top);
  // midtop = sdlgame::math::Vector2(centerx, top);
  // midleft = sdlgame::math::Vector2(left, centery);
  // midbottom = sdlgame::math::Vector2(centerx, bottom);
  // midright = sdlgame::math::Vector2(right, centery);
}
/**
 * @return a new rectangle that have been moved by given OFFSET x and y
 */
Rect &Rect::operator=(Rect oth) {
  x = left = oth.getLeft();
  y = top = oth.getTop();
  w = width = oth.getWidth();
  h = height = oth.getHeight();
  bottom = top + h;
  right = left + w;
  // size = sdlgame::math::Vector2(w, h);
  centerx = x + width / 2;
  centery = y + height / 2;
  // center = sdlgame::math::Vector2(centerx, centery);
  // topleft = sdlgame::math::Vector2(left, top);
  // bottomleft = sdlgame::math::Vector2(left, bottom);
  // bottomright = sdlgame::math::Vector2(right, bottom);
  // topright = sdlgame::math::Vector2(right, top);
  // midtop = sdlgame::math::Vector2(centerx, top);
  // midleft = sdlgame::math::Vector2(left, centery);
  // midbottom = sdlgame::math::Vector2(centerx, bottom);
  // midright = sdlgame::math::Vector2(right, centery);
  return *this;
}
bool Rect::operator==(const Rect &oth) const {
  if (this == &oth)
    return true;
  return x == oth.getLeft() and y == oth.getTop() and w == oth.getWidth() and
         h == oth.getHeight();
}
SDL_FRect Rect::to_SDL_FRect() const {
  SDL_FRect res = {static_cast<float>(x), static_cast<float>(y),
                   static_cast<float>(w), static_cast<float>(h)};
  return res;
}
/**
 * TEST: Approved
 */

Rect Rect::move(double offset_x, double offset_y) const {
  Rect res(x, y, w, h);
  res.x = res.left += offset_x;
  res.y = res.top += offset_y;
  res.bottom = res.top + res.h;
  res.right = res.left + res.w;
  res.centerx = res.x + res.width / 2;
  res.centery = res.y + res.height / 2;
  return res;
}

/**
 *  instead of a new one, this just move the rect that called this function
 * TEST: Approved
 */

void Rect::move_ip(double offset_x, double offset_y) {
  *this = move(offset_x, offset_y);
}
/**
 * @return a new rectangle that have been moved by given OFFSET x and y
 */
Rect Rect::move(sdlgame::math::Vector2 offset) const {
  return move(offset.x, offset.y);
}
/**
 *  instead of a new one, this just move the rect that called this function
 */
void Rect::move_ip(sdlgame::math::Vector2 offset) {
  *this = move(offset.x, offset.y);
}

/**
 * @return a new rectangle that changed the size to given OFFSET, the topleft of
 * the rectangle is remain still
 */

Rect Rect::inflate(double offset_w, double offset_h) const {
  Rect res(x, y, w, h);
  // res.size += sdlgame::math::Vector2(offset_w, offset_h);
  res.w = res.width += offset_w;
  res.h = res.height += offset_h;
  res.bottom = res.top + res.h;
  res.right = res.left + res.w;
  res.centerx = res.x + res.width / 2;
  res.centery = res.y + res.height / 2;
  return res;
}
Rect Rect::inflate(sdlgame::math::Vector2 offset) const {
  return inflate(offset.x, offset.y);
}
/**
 *  resize current rectangle with given offset, the topleft of the rectangle is
 * remain still
 */

void Rect::inflate_ip(double offset_w, double offset_h) {
  *this = inflate(offset_w, offset_h);
}
void Rect::inflate_ip(const sdlgame::math::Vector2 &offset) {
  *this = inflate(offset.x, offset.y);
}

/**
 *  to update the current rectangle that call the function
 */

void Rect::update(double _left, double _top, double _w, double _h) {
  x = left = _left;
  y = top = _top;
  w = width = _w;
  h = height = _h;
  bottom = top + h;
  right = left + w;
  centerx = x + width / 2;
  centery = y + height / 2;
}

void Rect::update(double _left, double _top, sdlgame::math::Vector2 _size) {
  x = left = _left;
  y = top = _top;
  w = width = _size.x;
  h = height = _size.y;
  bottom = top + h;
  right = left + w;
  // size = _size;
  centerx = x + width / 2;
  centery = y + height / 2;
  // center = sdlgame::math::Vector2(centerx, centery);
  // topleft = sdlgame::math::Vector2(left, top);
  // bottomleft = sdlgame::math::Vector2(left, bottom);
  // bottomright = sdlgame::math::Vector2(right, bottom);
  // topright = sdlgame::math::Vector2(right, top);
  // midtop = sdlgame::math::Vector2(centerx, top);
  // midleft = sdlgame::math::Vector2(left, centery);
  // midbottom = sdlgame::math::Vector2(centerx, bottom);
  // midright = sdlgame::math::Vector2(right, centery);
}

void Rect::update(sdlgame::math::Vector2 pos, double _w, double _h) {
  x = left = pos.x;
  y = top = pos.y;
  w = width = _w;
  h = height = _h;
  bottom = top + h;
  right = left + w;
  centerx = x + width / 2;
  centery = y + height / 2;
}
void Rect::update(sdlgame::math::Vector2 pos, sdlgame::math::Vector2 _size) {
  x = left = pos.x;
  y = top = pos.y;
  w = width = _size.x;
  h = height = _size.y;
  bottom = top + h;
  right = left + w;
  centerx = x + width / 2;
  centery = y + height / 2;
}
/**
 *  return a new rectangle that fit another rect but keep the aspect ratio of
 * the caller the position of the rect that return is the position of the caller
 */
Rect Rect::fit(const Rect oth) const {
  Rect res = *this;
  res.setSize(sdlgame::math::Vector2(w, h) * (oth.getWidth() / res.getWidth()));
  return res;
}
/**
 * @return return true if the other rect is completely inside the caller
 */
bool Rect::contains(const Rect oth) const {
  return left <= oth.getLeft() && right >= oth.getRight() &&
         top <= oth.getTop() && bottom >= oth.getBottom();
}

Rect Rect::overlap(const Rect &oth) {
  return (
      colliderect(oth)
          ? Rect(std::max(x, oth.getLeft()), std::max(y, oth.getTop()),
                 std::min(right, oth.getRight()) - std::max(x, oth.getLeft()),
                 std::min(bottom, oth.getBottom()) - std::max(y, oth.getTop()))
          : Rect());
}
void Rect::overlap_ip(const Rect &oth) { *this = overlap(oth); }
/**
 * TEST: approved
 */

bool Rect::collidepoint(double _x, double _y) const {
  return left <= _x and _x <= right and top <= _y and _y <= bottom;
}
/**
 * @return return whether the point in param is inside the caller or not
 */
bool Rect::collidepoint(const sdlgame::math::Vector2 point) {
  return left <= point.x and point.x <= right and top <= point.y and
         point.y <= bottom;
}
/**
 * @return return whether the caller collide with the other rect or not
 * TEST: Approved
 */
bool Rect::colliderect(const Rect oth) const {
  return !(left >= oth.getRight() || right <= oth.getLeft() ||
           top >= oth.getBottom() || bottom <= oth.getTop());
}

// bool collideline(const Vector2 start, const Vector2 end)
// {
//     double t = ((end.x - start.x) * (y - start.y) - (end.y - start.y) * (x -
//     start.x)) / ((end.x - start.x) * (y + h - start.y) - (end.y - start.y) *
//     (x + w - start.x)); double u = ((x - start.x) * (end.y - start.y) - (y -
//     start.y) * (end.x - start.x)) / ((end.x - start.x) * (y + h - start.y) -
//     (end.y - start.y) * (x + w - start.x));

// }
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
void Rect::setSize(const sdlgame::math::Vector2 &_size) {
  inflate_ip(_size - sdlgame::math::Vector2(w, h));
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
  move_ip(_x - right, 0);
}

void Rect::setBottom(double _y) {
  // std::cout << "Moved the rect by " << _y - y << " in y axis\n";
  move_ip(0, _y - bottom);
}

void Rect::setTopLeft(double _x, double _y) { move_ip(_x - x, _y - y); }
void Rect::setBottomLeft(double _x, double _y) {
  move_ip(_x - x, _y - bottom);
}
void Rect::setTopRight(double _x, double _y) {
  move_ip(_x - right, _y - y);
}
void Rect::setBottomRight(double _x, double _y) {
  move_ip(_x - right, _y - bottom);
}

void Rect::setTopLeft(const sdlgame::math::Vector2 &pos) {
  move_ip(pos - getTopLeft());
}
void Rect::setBottomLeft(const sdlgame::math::Vector2 &pos) {
  move_ip(pos - getBottomLeft());
}
void Rect::setTopRight(const sdlgame::math::Vector2 &pos) {
  move_ip(pos - getTopRight());
}
void Rect::setBottomRight(const sdlgame::math::Vector2 &pos) {
  move_ip(pos - getBottomRight());
}
void Rect::setCenter(double _x, double _y) {
  move_ip(_x - centerx, _y - centery);
}
void Rect::setCenter(sdlgame::math::Vector2 pos) {
  move_ip(pos.x - centerx, pos.y - centery);
}

void Rect::setMidTop(double _x, double _y) {
  move_ip(_x - centerx, _y - y);
}
void Rect::setMidTop(const sdlgame::math::Vector2 &pos) {
  move_ip(pos.x - centerx, pos.y - y);
}

void Rect::setMidBottom(double _x, double _y) {
  move_ip(_x - centerx, _y - bottom);
}
void Rect::setMidBottom(const sdlgame::math::Vector2 &pos) {
  move_ip(pos.x - centerx, pos.y - bottom);
}

void Rect::setMidLeft(double _x, double _y) {
  move_ip(_x - x, _y - centery);
}
void Rect::setMidLeft(const sdlgame::math::Vector2 &pos) {
  move_ip(pos.x - x, pos.y - centery);
}

void Rect::setMidRight(double _x, double _y) {
  move_ip(_x - right, _y - centery);
}
void Rect::setMidRight(const sdlgame::math::Vector2 &pos) {
  move_ip(pos.x - right, pos.y - centery);
}
double Rect::getWidth() const { return w; }
double Rect::getHeight() const { return h; }
double Rect::getTop() const { return y; }
double Rect::getLeft() const { return x; }
double Rect::getRight() const { return right; }
double Rect::getBottom() const { return bottom; }
double Rect::getCenterX() const { return centerx; }
double Rect::getCenterY() const { return centery; }
sdlgame::math::Vector2 Rect::getSize() const {
  return sdlgame::math::Vector2(w, h);
}
sdlgame::math::Vector2 Rect::getCenter() const {
  return sdlgame::math::Vector2(centerx, centery);
}
sdlgame::math::Vector2 Rect::getTopLeft() const {
  return sdlgame::math::Vector2(x, y);
}
sdlgame::math::Vector2 Rect::getTopRight() const {
  return sdlgame::math::Vector2(top, right);
}
sdlgame::math::Vector2 Rect::getBottomLeft() const {
  return sdlgame::math::Vector2(bottom, left);
}
sdlgame::math::Vector2 Rect::getBottomRight() const {
  return sdlgame::math::Vector2(bottom, right);
}
sdlgame::math::Vector2 Rect::getMidTop() const {
  return sdlgame::math::Vector2(centerx, top);
}
sdlgame::math::Vector2 Rect::getMidLeft() const {
  return sdlgame::math::Vector2(left, centery);
}
sdlgame::math::Vector2 Rect::getMidBottom() const {
  return sdlgame::math::Vector2(centerx, bottom);
}
sdlgame::math::Vector2 Rect::getMidRight() const {
  return sdlgame::math::Vector2(right, centery);
}

/**
 *  return a SDL_Rect object from this rect
 */
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
} // namespace sdlgame::rect