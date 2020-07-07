#pragma once

#include "Ray.h"
#include "Vec3.h"

class Camera
{
public:
   Camera()
   {
      using math::Vec3;
      constexpr size_t IMG_WIDTH = 640;
      constexpr size_t IMG_HEIGHT = 480u;
      constexpr double ASPECT_RATIO =
         static_cast<double>(IMG_WIDTH) / IMG_HEIGHT;

      constexpr double VIEWPORT_HEIGHT = 2.0;
      constexpr double VIEWPORT_WIDTH = ASPECT_RATIO * VIEWPORT_HEIGHT;
      constexpr double FOCAL_LENGTH = 1.0;

      origin_ = Vec3{0, 0, 0};
      horizontal_vp_ = Vec3{VIEWPORT_WIDTH, 0, 0};
      vertical_vp_ = Vec3{0, VIEWPORT_HEIGHT, 0};
      lower_left_corner_vp = origin_ - (horizontal_vp_ / 2) -
                             (vertical_vp_ / 2) - Vec3{0, 0, FOCAL_LENGTH};
   }

   math::Ray GetRay(double u, double v) const
   {
      return math::Ray(origin_, lower_left_corner_vp + u * horizontal_vp_ +
                             v * vertical_vp_ - origin_);
   }

private:
   math::Vec3 origin_;
   math::Vec3 lower_left_corner_vp;
   math::Vec3 horizontal_vp_;
   math::Vec3 vertical_vp_;
};