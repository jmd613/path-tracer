#include "Image.h"

#include <fstream>

Image::Image(std::string path, size_t width, size_t height) :
   path_(std::move(path)),
   pixels_(std::vector<math::Vec3>(width * height, math::Vec3())),
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
         file << color.GetX() << ' ' << color.GetY() << ' ' << color.GetZ()
              << '\n';
      }
   }
}

void Image::SetPixel(const math::Vec3 &color, size_t x, size_t y)
{
   pixels_.at(width_ * y + x) = color;
}

const math::Vec3 &Image::GetColor(size_t x, size_t y) const
{
   return pixels_.at(width_ * y + x);
}