#include "Image.h"

#include <fstream>
#include <utility>

namespace gfx {

Image::Image(size_t width, size_t height) :
   pixels_(std::vector<Pixel>(width * height, Pixel())),
   width_(width), height_(height)
{}

void WriteImage(const Image& img, const std::string &path)
{
   std::ofstream file;
   file.open(path, std::ofstream::trunc);

   auto width = img.GetWidth();
   auto height = img.GetHeight();

   // PPM Header
   file << "P3\n" << width << ' ' << height << "\n255\n";

   for (size_t y = 0; y < height; ++y)
   {
      for (size_t x = 0; x < width; ++x)
      {
         auto &color = img.GetColor(x, y);
         file << +color.r << ' ' << +color.g << ' ' << +color.b << '\n';
      }
   }
}

}   // namespace gfx