#pragma once

#include "Vec3.h"

namespace math {

class Ray
{
public:
   Ray() = default;
   Ray(const Vec3 &origin, const Vec3 &direction) :
      origin_(origin), direction_(direction)
   {}

   Vec3 GetOrigin() const { return origin_; }
   Vec3 GetDirection() const { return direction_; }

private:
   Vec3 origin_, direction_;
};

}   // namespace math