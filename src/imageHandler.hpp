#ifndef IMAGE_HANDLER_HPP
#define IMAGE_HANDLER_HPP

#include <cstdint>
#include <string>
#include <vector>

class ImageHandler {
public:
  std::uint32_t width;
  std::uint32_t height;
  std::vector<std::uint8_t> image;
  void decodePng(const std::string &filename);

  void encodePng(const std::string &filename);
};

#endif // IMAGE_HANDLER_HPP
