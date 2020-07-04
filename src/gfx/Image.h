#pragma once

#include <string>
#include <vector>

#include "Pixel.h"

namespace gfx {

// TODO: Determine coordinate system (currently top-right is 0,0)

class Image
{
public:
   Image(size_t width, size_t height);

   void SetPixel(const Pixel &pixel, size_t x, size_t y)
   {
      pixels_.at(width_ * y + x) = pixel;
   }

   const Pixel &GetColor(size_t x, size_t y) const
   {
      return pixels_.at(width_ * y + x);
   }

   size_t GetWidth() const { return width_; }
   size_t GetHeight() const { return height_; }

private:
   std::vector<Pixel> pixels_;
   const size_t width_, height_;
};

void WriteImage(const Image &img, const std::string &path);

}   // namespace gfx