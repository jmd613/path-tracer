#include "Camera.h"

using namespace math;

Vec3 GetRayColor(const Ray &ray, const IHittable &scene,
                       size_t depth)
{
   if (depth <= 0) return {0, 0, 0};

   constexpr double infinity = std::numeric_limits<double>::infinity();
   if (auto hit = scene.Hit(ray, 0.0001, infinity); hit)
   {
      if (auto rec = hit->mat->Scatter(ray, *hit); rec)
      {
         auto &[scattered, attenuation] = *rec;
         return attenuation * GetRayColor(scattered, scene, --depth);
      }
      return {0, 0, 0};
   }

   auto normal = ray.GetDirection().Normal();
   auto y_length = 0.5 * (normal.GetY() + 1);

   constexpr auto RED = Vec3{0.5, 0.7, 1.0};
   constexpr auto BLUE = Vec3{1, 1, 1};

   auto val = (1.0 - y_length) * BLUE + y_length * RED;
   return Vec3(val);
}

gfx::Pixel Camera::GetPixel(const Scene &scene, size_t x, size_t y,
                            size_t samples) const
{
   double r = 0, g = 0, b = 0;
   for (size_t s = 0; s < samples; ++s)
   {
      auto u = static_cast<double>(x + RandomDouble()) / (width_ - 1);
      auto v =
         static_cast<double>(height_ - y - 1 + RandomDouble()) / (height_ - 1);

      auto color_vec = GetRayColor(GetRay(u, v), scene, 50);
      r += color_vec.GetX();
      g += color_vec.GetY();
      b += color_vec.GetZ();
   }

   // Gamma correction (gamma = 2)
   const double SCALE = 1.0 / (samples);
   r = sqrt(SCALE * r);
   g = sqrt(SCALE * g);
   b = sqrt(SCALE * b);

   auto vec_pix = Vec3(r, g, b) * 255;
   return gfx::Pixel(vec_pix);
}