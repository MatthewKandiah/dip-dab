#include <vector>
#include <array>
#include <stdint.h>
#include "pixel.h"

class Image{
  public:
    int32_t height, width;
    const std::vector<int8_t> *source;

    Image(int32_t h, int32_t w, std::vector<int8_t> *s):
      height(h),
      width(w),
      source(s) {}

    Pixel getPixel(int32_t x, int32_t y) {
      const int32_t rValueIndex = 4 * (width * y + x);
      const int32_t gValueIndex = rValueIndex + 1;
      const int32_t bValueIndex = gValueIndex + 1;
      const int32_t aValueIndex = bValueIndex + 1;
      return Pixel((*source)[rValueIndex], (*source)[gValueIndex], (*source)[bValueIndex], (*source)[aValueIndex]);
    }
};
