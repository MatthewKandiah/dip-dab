#ifndef IMAGE_ENCODER_HPP
#define IMAGE_ENCODER_HPP

#include <cstdint>
#include <string>
#include <vector>

class ImageEncoder {
public:
  void encodePng(const std::string &filename, std::vector<std::uint8_t> &image,
                 std::uint32_t &width, std::uint32_t &height);
};

#endif // !IMAGE_ENCODER_HPP
