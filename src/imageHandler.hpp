#ifndef IMAGE_HANDLER_HPP
#define IMAGE_HANDLER_HPP

#include <cstdint>
#include <string>
#include <vector>

class ImageHandler {
public:
  ImageHandler(std::string filename) { decodePng(filename); }
  ImageHandler(
      std::vector<std::uint8_t> imageData,
      std::uint32_t w,
      std::uint32_t h
      ) {
    image = imageData;
    width = w;
    height = h;
  }

  std::uint32_t width;
  std::uint32_t height;
  std::vector<std::uint8_t> image;

  void decodePng(const std::string &filename);

  void encodePng(const std::string &filename);
};

#endif // IMAGE_HANDLER_HPP
