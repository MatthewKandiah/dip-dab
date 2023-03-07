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
      for (Pixel pixel : image.getPixels()) {
        uint8_t grey = greyscaleWeightedAverage(pixel.getRGBA());
        uint8_t alpha = pixel.getRGBA()[3];
        result.push_back(grey);
        result.push_back(grey);
        result.push_back(grey);
        result.push_back(alpha);
      }
      return result;
    }

  private:
    unsigned char greyscaleWeightedAverage(const std::array<uint8_t, 4> rgba) {
      // greyscale weighted average formula taken from https://goodcalculators.com/rgb-to-grayscale-conversion-calculator/
      return static_cast<char>(0.299*rgba[0] + 0.587*rgba[1] + 0.114*rgba[2]);
    }
 };

#endif
