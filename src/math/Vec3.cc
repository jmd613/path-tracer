#include "Vec3.h"

#include <cmath>

#include "Util.h"

namespace math {

double Vec3::Length() const { return sqrt(x_ * x_ + y_ * y_ + z_ * z_); }

Vec3 Vec3::Normal() const { return *this / Length(); }

Vec3 RandomVec3() { return {RandomDouble(), RandomDouble(), RandomDouble()}; }

Vec3 RandomVec3(double min, double max)
{
   return {RandomDouble(min, max), RandomDouble(min, max),
           RandomDouble(min, max)};
}

Vec3 RandomInUnitSphere()
{
   while (true)
   {
      auto p = RandomVec3(-1, 1);
      if (p.LengthSquared() >= 1) continue;
      return p;
   }
}

std::ostream &operator<<(std::ostream &os, const Vec3 &vec3)
{
   return os << "Vec3(" << vec3.x_ << ", " << vec3.y_ << ", " << vec3.z_ << ")";
}

}   // namespace math