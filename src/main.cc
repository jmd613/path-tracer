#include <limits>
#include <memory>
#include <numeric>

#include "Camera.h"
#include "Image.h"
#include "Material.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"
#include "Util.h"
#include "Vec3.h"

using namespace math;
using namespace gfx;

// Creates a vector following the lamertian distribution
Vec3 RandomLambertianVec()
{
   double a = math::RandomDouble(0, 2 * M_PI);
   double z = math::RandomDouble(-1, 1);
   double r = sqrt(1 - z * z);

   return {r * cos(a), r * sin(a), z};
}

// Determines the color from a given ray
Vec3 RayColor(const Ray &ray, const IHittable &scene, size_t depth)
{
   if (depth <= 0) return {0, 0, 0};

   constexpr double infinity = std::numeric_limits<double>::infinity();
   if (auto hit = scene.Hit(ray, 0.0001, infinity); hit)
   {
      if (auto rec = hit->mat->Scatter(ray, *hit); rec)
      {
         auto &[scattered, attenuation] = *rec;
         return attenuation * RayColor(scattered, scene, --depth);
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

Pixel CalcPixelColor(const Camera &camera, const Scene &scene, size_t x,
                     size_t y, size_t width, size_t height, size_t samples)
{
   double r = 0, g = 0, b = 0;
   for (size_t s = 0; s < samples; ++s)
   {
      auto u = static_cast<double>(x + RandomDouble()) / (width - 1);
      auto v =
         static_cast<double>(height - y - 1 + RandomDouble()) / (height - 1);
      auto ray = camera.GetRay(u, v);
      auto color_vec = RayColor(ray, scene, 50);
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
   return Pixel(vec_pix);
}

int main()
{
   constexpr size_t IMG_WIDTH = 640u;
   constexpr size_t IMG_HEIGHT = 480u;
   const Camera camera(IMG_WIDTH, IMG_HEIGHT);

   constexpr size_t SAMPLES_PER_PIXEL = 128;

   Scene scene;
   auto material_ground = std::make_shared<Lambertian>(Vec3(0.8, 0.8, 0.0));
   auto material_center = std::make_shared<Lambertian>(Vec3(0.7, 0.3, 0.3));
   auto material_left = std::make_shared<Metal>(Vec3(0.8, 0.8, 0.8), 0.2);
   auto material_right = std::make_shared<Metal>(Vec3(0.8, 0.6, 0.2), 1.0);

   scene.add(std::make_unique<Sphere>(Vec3(0.0, -100.5, -1.0), 100.0,
                                      material_ground));
   scene.add(
      std::make_unique<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5, material_center));
   scene.add(
      std::make_unique<Sphere>(Vec3(-1.0, 0.0, -1.0), 0.5, material_left));
   scene.add(
      std::make_unique<Sphere>(Vec3(1.0, 0.0, -1.0), 0.5, material_right));

//      scene.add(std::make_unique<Sphere>(Vec3(0, 0, -1), 0.5, material_left));
//      scene.add(std::make_unique<Sphere>(Vec3(0, -100.5, -1), 100, material_ground));

   Image img(IMG_WIDTH, IMG_HEIGHT);
   double current_percent = 0;
   for (size_t y = 0; y < IMG_HEIGHT; ++y)
   {
      for (size_t x = 0; x < IMG_WIDTH; ++x)
      {
         auto pixel = CalcPixelColor(camera, scene, x, y, IMG_WIDTH, IMG_HEIGHT,
                                     SAMPLES_PER_PIXEL);

         img.SetPixel(pixel, x, y);
      }
      current_percent += 1.0 / IMG_HEIGHT;
      std::cout << "Percent: " << current_percent * 100 << std::endl;
   }
   WriteImagePPM(img, "ray.ppm");
}
