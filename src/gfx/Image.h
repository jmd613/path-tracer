#pragma once

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

#include "Vec3.h"

namespace gfx {

// TOOD: Do something better than just wrapping a vector
struct Pixel
{
   Pixel() = default;
   Pixel(uint8_t r, uint8_t g, uint8_t b) :
      r(std::clamp(+r, 0, 255)), g(std::clamp(+g, 0, 255)),
      b(std::clamp(+b, 0, 255))
   {}
   explicit Pixel(const math::Vec3 &vec) :
      r(vec.GetX()), g(vec.GetY()), b(vec.GetZ())
   {}

   uint8_t r, g, b;
};

// TODO: Determine coordinate system (currently top-right is 0,0)

class Image
{
public:
   Image(size_t width, size_t height);

   void SetPixel(const Pixel &pixel, size_t idx)
   {
      assert(idx < width_ * height_);
      pixels_.at(idx) = pixel;
   }

   void SetPixel(const Pixel &pixel, size_t x, size_t y)
   {
      pixels_.at(width_ * y + x) = pixel;
   }

   [[nodiscard]] const Pixel &GetPixel(size_t idx) const
   {
      assert(idx < width_ * height_);
      return pixels_.at(idx);
   }

   [[nodiscard]] const Pixel &GetPixel(size_t x, size_t y) const
   {
      return pixels_.at(width_ * y + x);
   }

   [[nodiscard]] size_t GetWidth() const { return width_; }
   [[nodiscard]] size_t GetHeight() const { return height_; }

private:
   std::vector<Pixel> pixels_;
   const size_t width_, height_;
};

void WriteImagePPM(const Image &img, const std::string &path);

}   // namespace gfx