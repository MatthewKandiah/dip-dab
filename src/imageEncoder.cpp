#include "imageEncoder.hpp"
#include "lodepng/lodepng.h"
#include <cstdint>
#include <iostream>
#include <string>

void ImageEncoder::encodePng(const std::string &filename, std::vector<std::uint8_t> &image,
               std::uint32_t &width, std::uint32_t &height) {
  std::uint32_t error = lodepng::encode(filename.c_str(), image, width, height);

  if (error) {
    std::cout << "encoder error " << error << ": " << lodepng_error_text(error)
              << '\n';
  }
}
