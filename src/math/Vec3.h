#pragma once

#include <iostream>

namespace math {

class Vec3
{
public:
   constexpr Vec3() : x_(0.0), y_(0.0), z_(0.0) {}
   constexpr Vec3(double x, double y, double z) : x_(x), y_(y), z_(z) {}

   double GetX() const { return x_; }
   double GetY() const { return y_; }
   double GetZ() const { return z_; }

   double Length() const;

   constexpr double LengthSquared() const
   {
      return x_ * x_ + y_ * y_ + z_ * z_;
   }

   Vec3 Normal() const;

   constexpr Vec3 Cross(const Vec3 &other) const
   {
      double x = (y_ * other.z_) + (z_ * other.y_);
      double y = (z_ * other.x_) + (x_ * other.z_);
      double z = (x_ * other.y_) + (y_ * other.x_);
      return {x, y, z};
   }

   constexpr double Dot(const Vec3 &other) const
   {
      double x = x_ * other.x_;
      double y = y_ * other.y_;
      double z = z_ * other.z_;
      return x + y + z;
   }

   constexpr Vec3 operator+(const Vec3 &other) const
   {
      return {x_ + other.x_, y_ + other.y_, z_ + other.z_};
   }

   constexpr Vec3 &operator+=(const Vec3 &other)
   {
      x_ += other.x_;
      y_ += other.y_;
      z_ += other.z_;
      return *this;
   }

   constexpr Vec3 operator-() const { return {-x_, -y_, -z_}; }

   constexpr Vec3 operator-(const Vec3 &other) const
   {
      return {x_ - other.x_, y_ - other.y_, z_ - other.z_};
   }

   constexpr Vec3 &operator-=(const Vec3 &other)
   {
      x_ -= other.x_;
      y_ -= other.y_;
      z_ -= other.z_;
      return *this;
   }

   constexpr Vec3 operator*(const Vec3 &other) const
   {
      return {x_ * other.x_, y_ * other.y_, z_ * other.z_};
   }

   constexpr Vec3 &operator*=(const Vec3 &other)
   {
      x_ *= other.x_;
      y_ *= other.y_;
      z_ *= other.z_;
      return *this;
   }

   friend constexpr Vec3 operator*(double val, const Vec3 &vec)
   {
      return {val * vec.x_, val * vec.y_, val * vec.z_};
   }

   constexpr Vec3 operator*(double val) const
   {
      return {val * x_, val * y_, val * z_};
   }

   constexpr Vec3 &operator*=(double val)
   {
      x_ *= val;
      y_ *= val;
      z_ *= val;
      return *this;
   }

   friend constexpr Vec3 operator/(double val, const Vec3 &vec)
   {
      return {val / vec.x_, val / vec.y_, val / vec.z_};
   }

   constexpr Vec3 operator/(double val) const
   {
      return {x_ / val, y_ / val, z_ / val};
   }

   constexpr Vec3 &operator/=(double val)
   {
      x_ /= val;
      y_ /= val;
      z_ /= val;
      return *this;
   }

   constexpr bool operator==(const Vec3 &other) const
   {
      return (x_ == other.x_) && (y_ == other.y_) && (z_ == other.z_);
   }

   constexpr bool operator!=(const Vec3 &other) const
   {
      return !((x_ == other.x_) && (y_ == other.y_) && (z_ == other.z_));
   }

   friend std::ostream &operator<<(std::ostream &os, const Vec3 &vec3);

private:
   double x_, y_, z_;
};

Vec3 VecFromOriginDirection(const Vec3 &origin, const Vec3 &dir);
Vec3 RandomVec3();
Vec3 RandomVec3(double min, double max);
Vec3 RandomInUnitSphere();

inline Vec3 GetXNormal() { return {1, 0, 0}; }
inline Vec3 GetYNormal() { return {0, 1, 0}; }
inline Vec3 GetZNormal() { return {0, 0, 1}; }

}   // namespace math