#include "imageDecoder.hpp"
#include "lodepng/lodepng.h"
#include <iostream>

void ImageDecoder::decodePng(const std::string &filename, std::vector<std::uint8_t> &image,
               std::uint32_t &width, std::uint32_t &height) {
  std::uint32_t error = lodepng::decode(image, width, height, filename.c_str());

  if (error) {
    std::cout << "decoder error " << error << ": " << lodepng_error_text(error)
              << '\n';
  }
}
