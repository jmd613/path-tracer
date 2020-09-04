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
#include "Util.h"

using namespace math;
using namespace gfx;

// Creates a vector following the lamertian distribution
Vec3 RandomLambertianVec()
{
   double a = math::RandomDouble(0, 2 * M_PI);
   double z = math::RandomDouble(-1, 1);
   double r = sqrt(1 - z*z);

   return {r * cos(a), r * sin(a), z};
}

// Determines the color from a given ray
Vec3 RayColor(const Ray &ray, const IHittable &scene, size_t depth)
{
   if (depth <= 0) return {0, 0, 0};

   constexpr double infinity = std::numeric_limits<double>::infinity();
   if (auto hit = scene.Hit(ray, 0.0001, infinity); hit)
   {
      auto vec = hit->point + hit->normal + RandomLambertianVec();
      return 0.5 * RayColor(Ray(hit->point, vec - hit->point), scene, --depth);
   }

   auto normal = ray.GetDirection().Normal();
   auto y_length = 0.5 * (normal.GetY() + 1);

   constexpr auto RED = Vec3{0.5, 0.7, 1.0};
   constexpr auto BLUE = Vec3{1, 1, 1};

   auto val = (1.0 - y_length) * BLUE + y_length * RED;
   return Vec3(val);
}

int main()
{
   constexpr size_t IMG_WIDTH = 640;
   constexpr size_t IMG_HEIGHT = 480;
   const Camera camera(IMG_WIDTH, IMG_HEIGHT);

   constexpr size_t SAMPLES_PER_PIXEL = 32;

   Scene scene;
   scene.add(std::make_unique<Sphere>(Vec3(0, 0, -1), 0.5));
   scene.add(std::make_unique<Sphere>(Vec3(0, -100.5, -1), 100));

   Image img(IMG_WIDTH, IMG_HEIGHT);
   double current_percent = 0;
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
            auto color_vec = RayColor(ray, scene, 50);
            r += color_vec.GetX();
            g += color_vec.GetY();
            b += color_vec.GetZ();
         }

         // Gamma correction (gamma = 2)
         const double SCALE = 1.0 / (SAMPLES_PER_PIXEL);
         r = sqrt(SCALE * r);
         g = sqrt(SCALE * g);
         b = sqrt(SCALE * b);

         auto vec_pix = Vec3(r, g, b) * 255;
         auto pixel = Pixel(vec_pix);

         img.SetPixel(pixel, x, y);
      }
      current_percent += 1.0 / IMG_HEIGHT;
      std::cout << "Percent: " << current_percent * 100 << std::endl;
   }
   WriteImagePPM(img, "ray.ppm");
}
