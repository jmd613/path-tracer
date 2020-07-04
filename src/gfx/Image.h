#pragma once

#include <string>
#include <vector>

#include "Pixel.h"

namespace gfx {

class Image
{
public:
   Image(std::string path, size_t width, size_t height);
   ~Image();

   void SetPixel(const Pixel &pixel, size_t x, size_t y);
   const Pixel &GetColor(size_t x, size_t y) const;

private:
   std::string path_;
   std::vector<Pixel> pixels_;
   size_t width_, height_;
};

}   // namespace gfx