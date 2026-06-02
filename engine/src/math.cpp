#include "math.hpp"
#include "SDL2/SDL.h"
#include <cmath>
#include <algorithm>

#define M_PI 3.14159265358979323846

namespace sdlgame::math {
double degree_to_radian(double deg) { return deg * M_PI / 180.0; }
double radian_to_degree(double rad) { return rad * 180.0 / M_PI; }

double clamp(double val, double left, double right) {
  if (left > right)
    std::swap(left, right);
  return (val < left ? left : (val > right ? right : val));
}

Vector2::Vector2(const SDL_Point &p)
    : x(static_cast<double>(p.x)), y(static_cast<double>(p.y)) {}
Vector2::Vector2(double _x, double _y) : x(_x), y(_y) {}

Vector2 &Vector2::operator+=(const Vector2 &oth) {
  x += oth.x;
  y += oth.y;
  return *this;
}
Vector2 &Vector2::operator-=(const Vector2 &oth) {
  x -= oth.x;
  y -= oth.y;
  return *this;
}
Vector2 &Vector2::operator*=(const double &scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}
Vector2 &Vector2::operator/=(const double &scalar) {
  x /= scalar;
  y /= scalar;
  return *this;
}

Vector2 Vector2::operator+(const Vector2 &oth) const {
  return {x + oth.x, y + oth.y};
}
Vector2 Vector2::operator-() const { return Vector2(-x, -y); }
Vector2 Vector2::operator-(const Vector2 &oth) const {
  return {x - oth.x, y - oth.y};
}
Vector2 Vector2::operator*(const double &scalar) const {
  return Vector2(scalar * x, scalar * y);
}

bool Vector2::operator==(const Vector2 &oth) const {
  return x == oth.x and y == oth.y;
}

double Vector2::magnitude() const { return std::sqrt(x * x + y * y); }
double Vector2::sqr_magnitude() const { return x * x + y * y; }

Vector2 Vector2::normalize() const {
  double mag = magnitude();
  if (mag == 0) return {0, 0};
  return Vector2(x / mag, y / mag);
}

void Vector2::normalize_ip() { 
  double mag = magnitude();
  if (mag != 0) *this *= 1.0 / mag; 
}

double Vector2::dot(const Vector2 &oth) const { return x * oth.x + y * oth.y; }

double Vector2::angle_to(const Vector2 &oth) const {
  double mag1 = magnitude();
  double mag2 = oth.magnitude();
  if (mag1 == 0 || mag2 == 0) return 0;
  return std::acos(std::clamp(dot(oth) / (mag1 * mag2), -1.0, 1.0)) * 180.0 / M_PI;
}

Vector2 Vector2::rotate(double deg) const {
  double angleInRadians = degree_to_radian(deg);
  return Vector2(x * std::cos(angleInRadians) - y * std::sin(angleInRadians),
                 x * std::sin(angleInRadians) + y * std::cos(angleInRadians));
}

void Vector2::rotate_ip(double deg) {
  double _x = x, _y = y;
  double angleInRadians = degree_to_radian(deg);
  x = _x * std::cos(angleInRadians) - _y * std::sin(angleInRadians);
  y = _x * std::sin(angleInRadians) + _y * std::cos(angleInRadians);
}

double Vector2::distance_to(const Vector2 &oth) const {
  return std::sqrt((x - oth.x) * (x - oth.x) + (y - oth.y) * (y - oth.y));
}

Vector2 Vector2::reflect(const Vector2 &normal) const {
  return (*this) - normal * 2 * (dot(normal));
}

void Vector2::reflect_ip(const Vector2 &normal) { *this = reflect(normal); }

Vector2 Vector2::project(const Vector2 &normal) const {
  double sqr_mag = normal.sqr_magnitude();
  if (sqr_mag == 0) return {0, 0};
  return normal * (dot(normal) / sqr_mag);
}

void Vector2::project_ip(const Vector2 &normal) { *this = project(normal); }

std::string Vector2::toString() const {
  return "Vector2<" + std::to_string(x) + " , " + std::to_string(y) + ">";
}

SDL_FPoint Vector2::to_SDL_FPoint() const {
  return {static_cast<float>(x), static_cast<float>(y)};
}

Vector2 operator*(const double &scalar, const Vector2 &v) {
  return v * scalar;
}

} // namespace sdlgame::math
