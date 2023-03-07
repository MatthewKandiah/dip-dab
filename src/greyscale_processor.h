#ifndef GREYSCALE_PROCESSOR_H
#define GREYSCALE_PROCESSOR_H

#include <cstdint>
#include <vector>
#include <array>
#include "image.h"

class GreyscaleProcessor {
  public: 
    Image image;
    GreyscaleProcessor(Image x) : image(x) {} 

    std::vector<uint8_t> process() {
      std::vector<uint8_t> result {};
      for (Pixel pixel : image.getGreyscalePixels()) {
        result.push_back(pixel.r);
        result.push_back(pixel.g);
        result.push_back(pixel.b);
        result.push_back(pixel.a);
      }
      return result;
    }
 };

#endif
