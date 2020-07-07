#include <limits>

#include "Image.h"
#include "Ray.h"
#include "Vec3.h"
#include "Sphere.h"

using namespace math;
using namespace gfx;

Pixel RayColor(const Ray &ray)
{
   auto s = Sphere({0, 0 , -1}, 0.5);
   if (auto hit = s.Hit(ray, 0, std::numeric_limits<double>::infinity()))
   {
      auto norm = hit->normal;
      auto vec = 255 * Vec3(norm.GetX() + 1, norm.GetY() + 1, norm.GetZ() + 1);
      return Pixel(0.5 * vec);
   }

   auto normal = ray.GetDirection().Normal();
   auto y_length = 0.5 * (normal.GetY() + 1);

   constexpr auto RED = Vec3{0.5, 0.7, 1.0};
   constexpr auto BLUE = Vec3{1, 1, 1};

   auto val = (1.0 - y_length) * BLUE + y_length * RED;
   return Pixel(val * 255);
}

int main()
{
   constexpr size_t IMG_WIDTH = 640u;
   constexpr size_t IMG_HEIGHT = 480u ;
   constexpr double ASPECT_RATIO = static_cast<double>(IMG_WIDTH) / IMG_HEIGHT;

   constexpr double VIEWPORT_HEIGHT = 2.0;
   constexpr double VIEWPORT_WIDTH = ASPECT_RATIO * VIEWPORT_HEIGHT;
   constexpr double FOCAL_LENGTH = 1.0;

   constexpr auto ORIGIN = Vec3{0, 0, 0};
   constexpr auto HORIZONTAL_VP = Vec3{VIEWPORT_WIDTH, 0, 0};
   constexpr auto VERTICAL_VP = Vec3{0, VIEWPORT_HEIGHT, 0};
   constexpr auto LOWER_LEFT_CORNER_VP = ORIGIN - (HORIZONTAL_VP / 2) -
                                         (VERTICAL_VP / 2) -
                                         Vec3{0, 0, FOCAL_LENGTH};

   Image img(IMG_WIDTH, IMG_HEIGHT);
   for (size_t y = 0; y < IMG_HEIGHT; ++y)
   {
      for (size_t x = 0; x < IMG_WIDTH; ++x)
      {
         auto u = static_cast<double>(x) / (IMG_WIDTH - 1);
         auto v = static_cast<double>(IMG_HEIGHT - y - 1) / (IMG_HEIGHT - 1);
         auto ray = Ray(ORIGIN, LOWER_LEFT_CORNER_VP + (u * HORIZONTAL_VP) +
                                   (v * VERTICAL_VP) - ORIGIN);
         auto pixel = RayColor(ray);
         img.SetPixel(pixel, x, y);
      }
   }
   WriteImagePPM(img, "ray.ppm");
}
