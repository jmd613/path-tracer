#include <iostream>

#include "Image.h"
#include "Vec3.h"

int main()
{
   constexpr size_t width = 3440;
   constexpr size_t height = 1440;

   gfx::Image img(width, height);
   for (size_t y = 0; y < height; ++y)
   {
      for (size_t x = 0; x < width; ++x)
      {
         auto r = double(x) / (width - 1);
         auto g = double(height - 1 - y) / (height - 1);
         auto b = 0.25;

         auto ir = static_cast<uint8_t>(255 * r);
         auto ig = static_cast<uint8_t>(255 * g);
         auto ib = static_cast<uint8_t>(255 * b);

         img.SetPixel({ir, ig, ib}, x, y);
      }
   }
   gfx::WriteImage(img, "test.ppm");
}