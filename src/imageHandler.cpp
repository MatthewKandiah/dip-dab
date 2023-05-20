#include "imageHandler.hpp"
#include "lodepng/lodepng.h"
#include <iostream>

void ImageHandler::decodePng(const std::string &filename, std::vector<std::uint8_t> &image, std::uint32_t &width, std::uint32_t &height) {
  std::uint32_t error = lodepng::decode(image, width, height, filename.c_str());

  if (error) {
    std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << '\n';
  }
}

void ImageHandler::encodePng(const std::string &filename, std::vector<std::uint8_t> &image, std::uint32_t &width, std::uint32_t &height) {
  std::uint32_t error = lodepng::encode(filename.c_str(), image, width, height);

  if (error) {
    std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << '\n';
  }
}

