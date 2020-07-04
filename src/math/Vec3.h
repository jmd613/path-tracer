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

   Vec3 Normal() const;
   constexpr Vec3 Cross(const Vec3 &other) const;
   constexpr double Dot(const Vec3 &other) const;

   constexpr Vec3 operator+(const Vec3 &other) const;
   constexpr Vec3 &operator+=(const Vec3 &other);

   constexpr Vec3 operator-() const;   // Negation Operator
   constexpr Vec3 operator-(const Vec3 &other) const;
   constexpr Vec3 &operator-=(const Vec3 &other);

   constexpr Vec3 operator*(const Vec3 &other) const;
   constexpr Vec3 &operator*=(const Vec3 &other);

   friend constexpr Vec3 operator*(double val, const Vec3 &vec);
   constexpr Vec3 operator*(double val) const;
   constexpr Vec3 &operator*=(double val);

   friend constexpr Vec3 operator/(double val, const Vec3 &vec);
   constexpr Vec3 operator/(double val) const;
   constexpr Vec3 &operator/=(double val);

   constexpr bool operator==(const Vec3 &other) const;
   constexpr bool operator!=(const Vec3 &other) const;

   friend std::ostream &operator<<(std::ostream &os, const Vec3 &vec3);

private:
   double x_, y_, z_;
};

Vec3 VecFromOriginDirection(const Vec3 &origin, const Vec3 &dir);

inline Vec3 GetXNormal() { return {1, 0, 0}; }
inline Vec3 GetYNormal() { return {0, 1, 0}; }
inline Vec3 GetZNormal() { return {0, 0, 1}; }

}   // namespace math