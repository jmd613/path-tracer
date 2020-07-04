#pragma once

#include "Vec3.h"

#include <vector>

class Image
{
public:
   Image(std::string path, size_t width, size_t height);
   ~Image();

   void SetPixel(const math::Vec3 &color, size_t x, size_t y);
   const math::Vec3 &GetColor(size_t x, size_t y) const;
private:
   std::string path_;
   std::vector<math::Vec3> pixels_;
   size_t width_, height_;
};