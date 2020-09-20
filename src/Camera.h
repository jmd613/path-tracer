#pragma once

#include "Image.h"
#include "Material.h"
#include "Ray.h"
#include "Scene.h"
#include "Util.h"
#include "Vec3.h"

class Camera
{
public:
   Camera(size_t img_width, size_t img_height) :
      width_(img_width), height_(img_height)
   {
      using math::Vec3;
      double ar = static_cast<double>(img_width) / img_height;

      double VIEWPORT_HEIGHT = 2.0;
      double VIEWPORT_WIDTH = ar * VIEWPORT_HEIGHT;
      double FOCAL_LENGTH = 1.0;

      origin_ = Vec3{0, 0, 0};
      horizontal_vp_ = Vec3{VIEWPORT_WIDTH, 0, 0};
      vertical_vp_ = Vec3{0, VIEWPORT_HEIGHT, 0};
      lower_left_corner_vp = origin_ - (horizontal_vp_ / 2) -
                             (vertical_vp_ / 2) - Vec3{0, 0, FOCAL_LENGTH};
   }

   math::Ray GetRay(double u, double v) const
   {
      return math::Ray(origin_, lower_left_corner_vp + (u * horizontal_vp_) +
                                   (v * vertical_vp_) - origin_);
   }

   gfx::Pixel GetPixel(const Scene &scene, size_t x, size_t y,
                       size_t samples) const;

private:
   math::Vec3 origin_;
   math::Vec3 lower_left_corner_vp;
   math::Vec3 horizontal_vp_;
   math::Vec3 vertical_vp_;
   size_t width_;
   size_t height_;
};