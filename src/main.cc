#include <iostream>

#include "Image.h"
#include "Vec3.h"

int main()
{
   constexpr size_t width = 256;
   constexpr size_t height = 256;

   gfx::Image img("test.ppm", width, height);
   for (int y = height - 1; y >= 0; --y)
   {
      for (int x = 0; x < width; ++x)
      {
         auto r = double(x) / (width - 1);
         auto g = double(y) / (height - 1);
         auto b = 0.25;

         auto ir = static_cast<uint8_t>(255.999 * r);
         auto ig = static_cast<uint8_t>(255.999 * g);
         auto ib = static_cast<uint8_t>(255.999 * b);

         img.SetPixel({ir, ig, ib}, x, y);
      }
   }
}