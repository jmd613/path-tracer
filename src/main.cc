#include <iostream>

#include "Image.h"
#include "Vec3.h"

int main()
{
   constexpr size_t width = 256;
   constexpr size_t height = 256;

   Image img("test.ppm", width, height);
   for (int y = height - 1; y >= 0; --y)
   {
      for (int x = 0; x < width; ++x)
      {
         auto r = double(x) / (width - 1);
         auto g = double(y) / (height - 2);
         auto b = 0.25;

         int ir = static_cast<int>(255.999 * r);
         int ig = static_cast<int>(255.999 * g);
         int ib = static_cast<int>(255.999 * b);

         img.SetPixel(math::Vec3(ir, ig, ib), x, y);
      }
   }
}