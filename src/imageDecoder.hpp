#ifndef IMAGE_DECODER_HPP
#define IMAGE_DECODER_HPP

#include <cstdint>
#include <vector>

class ImageDecoder {
public:
  void decodePng(const std::string &filename, std::vector<std::uint8_t> &image,
                 std::uint32_t &width, std::uint32_t &height);
};

#endif // IMAGE_DECODER_HPPIMAGE_DECODER_HPP
