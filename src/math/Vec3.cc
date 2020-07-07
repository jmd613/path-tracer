#include "Vec3.h"

#include <cmath>

namespace math {

double Vec3::Length() const
{
   return sqrt(x_*x_ + y_*y_ + z_*z_);
}

Vec3 Vec3::Normal() const { return *this / Length(); }

std::ostream &operator<<(std::ostream &os, const Vec3 &vec3)
{
   return os << "Vec3(" << vec3.x_ << ", " << vec3.y_ << ", " << vec3.z_ << ")";
}

}   // namespace math