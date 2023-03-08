#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <array>
#include <stdint.h>
#include <cassert>
#include "pixel.h"

class Image{
  public:
    int32_t height, width;
    const std::vector<uint8_t> source;

    Image(int32_t h, int32_t w, std::vector<uint8_t> s):
      height(h),
      width(w),
      source(s) {
        // height and width are in terms of pixels, which each have 4 ints
        assert(4 * height * width == source.size());
      }

    Pixel getPixel(int32_t x, int32_t y) {
      const int32_t rValueIndex = 4 * (width * y + x);
      const int32_t gValueIndex = rValueIndex + 1;
      const int32_t bValueIndex = gValueIndex + 1;
      const int32_t aValueIndex = bValueIndex + 1;
      return Pixel(source[rValueIndex], source[gValueIndex], source[bValueIndex], source[aValueIndex]);
    }

    Pixel getGreyscalePixel(int32_t x, int32_t y) {
      auto pixel = getPixel(x, y);
      const int32_t grey = 0.299*pixel.r + 0.587*pixel.g + 0.114*pixel.b;  
      return Pixel(grey, grey, grey, pixel.a);
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

    std::vector<Pixel> getGreyscalePixels() {
      std::vector<Pixel> result {};
      for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
          result.push_back(getGreyscalePixel(j,i));
        }
      }
      return result;
    }
};

#endif
