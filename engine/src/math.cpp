#include "math.hpp"
#include "SDL2/SDL.h"

#define M_PI 3.14159265358979323846

namespace sdlgame::math
{
    double degree_to_radian(double deg)
    {
        return deg * M_PI / 180.0;
    }
    double radian_to_degree(double rad)
    {
        return rad * 180.0 / M_PI;
    }
    double clamp(double val, double l, double r)
    {
        if (l > r)
            std::swap(l, r);
        return (val < l ? l : (val > r ? r : val));
    }
    Vector2::Vector2()
    {
        x = 0;
        y = 0;
    }
    Vector2::Vector2(const SDL_Point &p)
    {
        x = (double)p.x;
        y = (double)p.y;
    }
    Vector2::Vector2(const Vector2 &oth)
    {
        x = oth.x;
        y = oth.y;
    }
    Vector2::Vector2(double _x, double _y)
    {
        x = _x;
        y = _y;
    }
    Vector2 &Vector2::operator=(const Vector2 &oth)
    {
        if (this != &oth)
        {
            x = oth.x;
            y = oth.y;
        }
        return *this;
    }
    Vector2 &Vector2::operator+=(const Vector2 &oth)
    {
        if (this != &oth)
        {
            x += oth.x;
            y += oth.y;
        }
        return *this;
    }
    Vector2 &Vector2::operator-=(const Vector2 &oth)
    {
        if (this != &oth)
        {
            x -= oth.x;
            y -= oth.y;
        }
        return *this;
    }
    Vector2 &Vector2::operator*=(const double &scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vector2 Vector2::operator+(const Vector2 &oth) const
    {
        return Vector2(x + oth.x, y + oth.y);
    }
    Vector2 Vector2::operator-() const
    {
        return Vector2(-x, -y);
    }
    Vector2 Vector2::operator-(const Vector2 &oth) const
    {
        return Vector2(x - oth.x, y - oth.y);
    }
    Vector2 Vector2::operator*(const double &scalar) const
    {
        return Vector2(scalar * x, scalar * y);
    }

    bool Vector2::operator==(const Vector2 &oth) const
    {
        return x == oth.x and y == oth.y;
    }
    /**
     * @return length of the vector
     */
    double Vector2::magnitude() const
    {
        return sqrt(x * x + y * y);
    }
    /**
     * @return the squared value of the length of the vector
     */
    double Vector2::sqr_magnitude() const
    {
        return x * x + y * y;
    }
    /**
     * @return a normalized vector (a vector with length 1 unit) that have the same direction with the original
     */
    Vector2 Vector2::normalize() const
    {
        return Vector2(x / this->magnitude(), y / this->magnitude());
    }
    /**
     *  normalize the vector
     */
    void Vector2::normalize_ip()
    {
        x /= this->magnitude();
        y /= this->magnitude();
    }
    /**
     * @return dot product between 2 vector
     */
    double Vector2::dot(const Vector2 &oth) const
    {
        return x * oth.x + y * oth.y;
    }
    /**
     * @return angle in degree to another vector in range [0,180] degrees, which is the smallest of 2 angle
     * */
    double Vector2::angle_to(const Vector2 &oth) const
    {
        return acos(this->dot(oth) / (this->magnitude() * oth.magnitude())) * 180.0 / M_PI;
    }

    /**
     * @return a vector that rotated deg degrees counter clockwise
     * */
    Vector2 Vector2::rotate(double deg) const
    {
        double angleInRadians = degree_to_radian(deg);
        return Vector2(x * cos(angleInRadians) - y * sin(angleInRadians), x * sin(angleInRadians) + y * cos(angleInRadians));
    }
    /**
     *  make the vector rotate deg degrees counter-clockwise
     */
    void Vector2::rotate_ip(double deg)
    {
        double _x = x, _y = y, angleInRadians = degree_to_radian(deg);
        x = _x * cos(angleInRadians) - _y * sin(angleInRadians);
        y = x * sin(angleInRadians) + y * cos(angleInRadians);
    }
    /**
     * @return distance between 2 point
     */
    double Vector2::distance_to(const Vector2 &oth) const
    {
        return sqrt((x - oth.x) * (x - oth.x) + (y - oth.y) * (y - oth.y));
    }
    /**
     * @return the vector that is the reflection of the current vector to a normal vector
     */
    Vector2 Vector2::reflect(const Vector2 &normal) const
    {
        return (*this) - normal * 2 * (this->dot(normal));
    }
    /**
     * reflect the vector through a normal vector
     */
    void Vector2::reflect_ip(const Vector2 &normal)
    {
        *this = this->reflect(normal);
    }
    /**
     * @return a projected vector from this vector to a normal vector
     */
    Vector2 Vector2::project(const Vector2 &normal) const
    {
        return normal * (this->dot(normal) / (normal.sqr_magnitude()));
    }
    /**
     * project the vector onto a normal vector
     */
    void Vector2::project_ip(const Vector2 &normal)
    {
        *this = this->project(normal);
    }
    std::string Vector2::toString() const
    {
        return "Vector2<" + std::to_string(x) + " , " + std::to_string(y) + ">";
    }

    Vector2 operator*(const double &scalar, const Vector2 &v)
    {
        return Vector2(scalar * v.x, scalar * v.y);
    }
    SDL_FPoint Vector2::to_SDL_FPoint() const
    {
        SDL_FPoint res = {(float)this->x, (float)this->y};
        return res;
    }
}