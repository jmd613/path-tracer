#include "Vec3.h"

#include <cmath>

namespace math {

double Vec3::Length() const
{
   return sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2));
}

Vec3 Vec3::Normal() const { return *this / Length(); }

constexpr Vec3 Vec3::Cross(const Vec3 &other) const
{
   double x = (y_ * other.z_) + (z_ * other.y_);
   double y = (z_ * other.x_) + (x_ * other.z_);
   double z = (x_ * other.y_) + (y_ * other.x_);
   return {x, y, z};
}

constexpr double Vec3::Dot(const Vec3 &other) const
{
   double x = x_ * other.x_;
   double y = y_ * other.y_;
   double z = z_ * other.z_;
   return x + y + z;
}

constexpr Vec3 Vec3::operator+(const Vec3 &other) const
{
   return {x_ + other.x_, y_ + other.y_, z_ + other.z_};
}

constexpr Vec3 &Vec3::operator+=(const Vec3 &other)
{
   x_ += other.x_;
   y_ += other.y_;
   z_ += other.z_;
   return *this;
}

constexpr Vec3 Vec3::operator-() const { return {-x_, -y_, -z_}; }

constexpr Vec3 Vec3::operator-(const Vec3 &other) const
{
   return {x_ - other.x_, y_ - other.y_, z_ - other.z_};
}

constexpr Vec3 &Vec3::operator-=(const Vec3 &other)
{
   x_ -= other.x_;
   y_ -= other.y_;
   z_ -= other.z_;
   return *this;
}

constexpr Vec3 Vec3::operator*(const Vec3 &other) const
{
   return {x_ * other.x_, y_ * other.y_, z_ * other.z_};
}

constexpr Vec3 &Vec3::operator*=(const Vec3 &other)
{
   x_ *= other.x_;
   y_ *= other.y_;
   z_ *= other.z_;
   return *this;
}

constexpr Vec3 operator*(double val, const Vec3 &vec)
{
   return {val * vec.x_, val * vec.y_, val * vec.z_};
}

constexpr Vec3 Vec3::operator*(double val) const
{
   return {val * x_, val * y_, val * z_};
}

constexpr Vec3 &Vec3::operator*=(double val)
{
   x_ *= val;
   y_ *= val;
   z_ *= val;
   return *this;
}

constexpr Vec3 operator/(double val, const Vec3 &vec)
{
   return {val / vec.x_, val / vec.y_, val / vec.z_};
}

constexpr Vec3 Vec3::operator/(double val) const
{
   return {x_ / val, y_ / val, z_ / val};
}

constexpr Vec3 &Vec3::operator/=(double val)
{
   x_ /= val;
   y_ /= val;
   z_ /= val;
   return *this;
}

constexpr bool Vec3::operator==(const Vec3 &other) const
{
   return (x_ == other.x_) && (y_ == other.y_) && (z_ == other.z_);
}

constexpr bool Vec3::operator!=(const Vec3 &other) const
{
   return !((x_ == other.x_) && (y_ == other.y_) && (z_ == other.z_));
}

std::ostream &operator<<(std::ostream &os, const Vec3 &vec3)
{
   return os << "Vec3(" << vec3.x_ << ", " << vec3.y_ << ", " << vec3.z_ << ")";
}

}   // namespace math