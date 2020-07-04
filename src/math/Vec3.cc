#include "Vec3.h"

#include <cmath>

namespace math {

double Vec3::Length() const
{
   return sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2));
}

Vec3 Vec3::Normal() const { return *this / Length(); }

std::ostream &operator<<(std::ostream &os, const Vec3 &vec3)
{
   return os << "Vec3(" << vec3.x_ << ", " << vec3.y_ << ", " << vec3.z_ << ")";
}

}   // namespace math