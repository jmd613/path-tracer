#include <limits>
#include <memory>
#include <numeric>
#include <random>

#include "Camera.h"
#include "Image.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"
#include "Vec3.h"

using namespace math;
using namespace gfx;

double RandomDouble()
{
   static std::uniform_real_distribution<double> distribution(0.0, 1.0);
   static std::mt19937 generator;
   return distribution(generator);
}

Vec3 RayColor(const Ray &ray, const IHittable &scene)
{
   constexpr double infinity = std::numeric_limits<double>::infinity();
   if (auto hit = scene.Hit(ray, 0, infinity); hit)
   {
      auto norm = hit->normal;
      auto vec = 255 * Vec3(norm.GetX() + 1, norm.GetY() + 1, norm.GetZ() + 1);
      return Vec3(0.5 * vec);
   }

   auto normal = ray.GetDirection().Normal();
   auto y_length = 0.5 * (normal.GetY() + 1);

   constexpr auto RED = Vec3{0.5, 0.7, 1.0};
   constexpr auto BLUE = Vec3{1, 1, 1};

   auto val = (1.0 - y_length) * BLUE + y_length * RED;
   return Vec3(val * 255);
}

int main()
{
   constexpr size_t IMG_WIDTH = 640u;
   constexpr size_t IMG_HEIGHT = 480u;
   const Camera camera(IMG_WIDTH, IMG_HEIGHT);

   constexpr size_t SAMPLES_PER_PIXEL = 10;

   Scene scene;
   scene.add(std::make_unique<Sphere>(Vec3(0, 0, -1), 0.5));
   scene.add(std::make_unique<Sphere>(Vec3(0, -100.5, -1), 100));

   Image img(IMG_WIDTH, IMG_HEIGHT);
   for (size_t y = 0; y < IMG_HEIGHT; ++y)
   {
      for (size_t x = 0; x < IMG_WIDTH; ++x)
      {
         double r = 0, g = 0, b = 0;
         for (size_t samples = 0; samples < SAMPLES_PER_PIXEL; ++samples)
         {
            auto u = static_cast<double>(x + RandomDouble()) / (IMG_WIDTH - 1);
            auto v = static_cast<double>(IMG_HEIGHT - y - 1 + RandomDouble()) /
                     (IMG_HEIGHT - 1);
            auto ray = camera.GetRay(u, v);
            auto color_vec = RayColor(ray, scene);
            r += color_vec.GetX();
            g += color_vec.GetY();
            b += color_vec.GetZ();
         }

         auto vec_pix = Vec3(r, g, b);
         vec_pix /= SAMPLES_PER_PIXEL;
         auto pixel = Pixel(vec_pix);

         img.SetPixel(pixel, x, y);
      }
   }
   WriteImagePPM(img, "ray.ppm");
}
