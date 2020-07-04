#include "Image.h"

#include <fstream>
#include <utility>

namespace gfx {

Image::Image(size_t width, size_t height) :
   pixels_(std::vector<Pixel>(width * height, Pixel())), width_(width),
   height_(height)
{}

void WriteImagePPM(const Image &img, const std::string &path)
{
   std::ofstream file;
   file.open(path, std::ofstream::trunc);

   auto width = img.GetWidth();
   auto height = img.GetHeight();

   // PPM Header
   file << "P3\n" << width << ' ' << height << "\n255\n";

   for (size_t idx = 0; idx  < width * height; ++idx)
   {
      auto pix = img.GetPixel(idx);
      file << +pix.r << ' ' << +pix.g << ' ' << +pix.b << '\n';
   }
}

}   // namespace gfx