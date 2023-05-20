#ifndef IMAGE_HANDLER_HPP
#define IMAGE_HANDLER_HPP

#include <cstdint>
#include <string>
#include <vector>

class ImageHandler {
public:
  void decodePng(const std::string &filename, std::vector<std::uint8_t> &image,
                 std::uint32_t &width, std::uint32_t &height);

  void encodePng(const std::string &filename, std::vector<std::uint8_t> &image,
                 std::uint32_t &width, std::uint32_t &height);
};

#endif // IMAGE_HANDLER_HPP
