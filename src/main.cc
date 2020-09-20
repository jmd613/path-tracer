#include <cmath>
#include <memory>

#include "Camera.h"
#include "Image.h"
#include "Material.h"
#include "Scene.h"
#include "Sphere.h"
#include "Vec3.h"

using namespace math;
using namespace gfx;

int main()
{
   constexpr size_t IMG_WIDTH = 640u;
   constexpr size_t IMG_HEIGHT = 480u;
   const Camera camera(IMG_WIDTH, IMG_HEIGHT);

   constexpr size_t SAMPLES_PER_PIXEL = 128;

   Scene scene;
   auto material_ground = std::make_shared<Lambertian>(Vec3(0.8, 0.8f, 0.0));
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

   Image img(IMG_WIDTH, IMG_HEIGHT);
   double current_percent = 0;
   for (size_t y = 0; y < IMG_HEIGHT; ++y)
   {
      for (size_t x = 0; x < IMG_WIDTH; ++x)
      {
         auto pixel = camera.GetPixel(scene, x, y, SAMPLES_PER_PIXEL);
         img.SetPixel(pixel, x, y);
      }
      current_percent += 1.0 / IMG_HEIGHT;
      std::cout << "Percent: " << current_percent * 100 << std::endl;
   }
   WriteImagePPM(img, "ray.ppm");
}
