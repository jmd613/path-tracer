#pragma once

#include "Vec3.h"

namespace math {

class Ray
{
public:
   Ray() = default;
   Ray(const Vec3 &origin, const Vec3 &direction) :
      origin_(origin), direction_(direction.Normal())
   {}

   Vec3 GetOrigin() const { return origin_; }
   Vec3 GetDirection() const { return direction_; }

   Vec3 PositionAt(double dist) const { return origin_ + (direction_ * dist); }

private:
   Vec3 origin_, direction_;
};

}   // namespace math