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

Image RenderImage(size_t width, size_t height, size_t samples,
                  const Scene &scene, const Camera &camera)
{
   Image img(width, height);
   double current_percent = 0;
   for (size_t y = 0; y < height; ++y)
   {
      for (size_t x = 0; x < width; ++x)
      {
         auto pixel = camera.GetPixel(scene, x, y, samples);
         img.SetPixel(pixel, x, y);
      }
      current_percent += 1.0 / height;
      std::cout << "Percent: " << current_percent * 100 << std::endl;
   }
   return img;
}

int main()
{
   constexpr size_t WIDTH = 1920u;
   constexpr size_t HEIGHT = 1080u;
   constexpr size_t SAMPLES_PER_PIXEL = 256u;
   const Camera camera(WIDTH, HEIGHT);

   Scene scene;
   auto material_ground = std::make_shared<Lambertian>(Vec3(0.8, 0.8, 0.0));
   auto material_center = std::make_shared<Lambertian>(Vec3(0.7, 0.3, 0.3));
   auto material_left = std::make_shared<Metal>(Vec3(0.8, 0.8, 0.8), 0.0);
   auto material_right = std::make_shared<Metal>(Vec3(0.8, 0.6, 0.2), 0.6);

   scene.add(std::make_unique<Sphere>(Vec3(0.0, -100.5, -1.0), 100.0,
                                      material_ground));
   scene.add(
      std::make_unique<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5, material_center));
   scene.add(
      std::make_unique<Sphere>(Vec3(-1.0, 0.0, -1.0), 0.5, material_left));
   scene.add(
      std::make_unique<Sphere>(Vec3(1.0, 0.0, -1.0), 0.5, material_right));

   Image img = RenderImage(WIDTH, HEIGHT, SAMPLES_PER_PIXEL, scene, camera);
   WriteImagePPM(img, "ray.ppm");
}
