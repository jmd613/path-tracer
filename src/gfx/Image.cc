#include "Image.h"

#include <fstream>
#include <utility>

namespace gfx {

Image::Image(std::string path, size_t width, size_t height) :
   path_(std::move(path)), pixels_(std::vector<Pixel>(width * height, Pixel())),
   width_(width), height_(height)
{}

Image::~Image()
{
   std::ofstream file;
   file.open(path_, std::ofstream::trunc);

   // PPM Header
   file << "P3\n" << width_ << ' ' << height_ << "\n255\n";

   for (int y = height_ - 1; y >= 0; --y)
   {
      for (int x = 0; x < width_; ++x)
      {
         auto &color = GetColor(x, y);
         file << +color.r << ' ' << +color.g << ' ' << +color.b << '\n';
      }
   }
}

void Image::SetPixel(const Pixel &color, size_t x, size_t y)
{
   pixels_.at(width_ * y + x) = color;
}

const Pixel &Image::GetColor(size_t x, size_t y) const
{
   return pixels_.at(width_ * y + x);
}

}   // namespace gfx