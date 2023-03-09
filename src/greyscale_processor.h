#ifndef GREYSCALE_PROCESSOR_H
#define GREYSCALE_PROCESSOR_H

#include "image.h"
#include <array>
#include <cstdint>
#include <vector>

class GreyscaleProcessor {
public:
  Image image;
  GreyscaleProcessor(Image x) : image(x) {}

  Image process() {
    std::vector<uint8_t> result{};
    for (Pixel pixel : image.getGreyscalePixels()) {
      result.push_back(pixel.r);
      result.push_back(pixel.g);
      result.push_back(pixel.b);
      result.push_back(pixel.a);
    }
    return Image(image.height, image.width, result);
  }
};

#endif
