#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <array>
#include <stdint.h>
#include "pixel.h"

class Image{
  public:
    int32_t height, width;
    const std::vector<uint8_t> source;

    Image(int32_t h, int32_t w, std::vector<uint8_t> s):
      height(h),
      width(w),
      source(s) {}

    Pixel getPixel(int32_t x, int32_t y) {
      const int32_t rValueIndex = 4 * (width * y + x);
      const int32_t gValueIndex = rValueIndex + 1;
      const int32_t bValueIndex = gValueIndex + 1;
      const int32_t aValueIndex = bValueIndex + 1;
      return Pixel(source[rValueIndex], source[gValueIndex], source[bValueIndex], source[aValueIndex]);
    }

    std::vector<Pixel> getPixels() {
      std::vector<Pixel> result {};
      for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
          result.push_back(getPixel(j, i));
        }
      }
      return result;
    }

};

#endif
