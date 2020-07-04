#pragma once

#include <cassert>
#include <string>
#include <vector>

namespace gfx {

struct Pixel
{
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