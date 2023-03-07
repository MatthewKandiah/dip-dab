#ifndef FILTER_H
#define FILTER_H

#include <cstdint>
#include <vector>
#include <cassert>
#include <array>
#include "image.h"
#include "pixel.h"

class Filter {
  public:
    const uint32_t width, height;
    std::vector<std::vector<uint32_t>> data;
    Filter(std::vector<std::vector<uint32_t>> x):
      data(x),
      width(x.size()),
      height(x[0].size()) {
        // filter must have odd dimensions, or it can't be centred on a pixel
        assert(width % 2 == 1);
        assert(height % 2 == 1);
      }

    Pixel apply(Image image, uint32_t xIndex, uint32_t yIndex) {
      std::vector<std::vector<Pixel>> pixelNeighborhood = getPixelNeighborhood(image, xIndex, yIndex);
      uint32_t result = 0;
      uint32_t normalisationFactor = 0;
      for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
          const Pixel pixel = pixelNeighborhood[i][j];
          // pixel must be greyscale for filter to be reasonably applied
          assert(pixel.r == pixel.g && pixel.g == pixel.b);
          result += pixel.r * data[i][j];
          normalisationFactor+= data[i][j];
        }
      }
      uint8_t grey = result / normalisationFactor;
      uint8_t alpha = image.getPixel(xIndex, yIndex).a;
      return Pixel(grey, grey, grey, alpha);
    }

  private:
    std::vector<std::vector<Pixel>> getPixelNeighborhood(Image image, uint32_t xIndex, uint32_t yIndex) {
      std::vector<std::vector<Pixel>> result {};
      for (int i = 0; i < height; i++) {
        uint32_t yIndexInImage = yIndex - ((height-1)/2) + i;
        std::vector<Pixel> pixelRow {};
        for (int j = 0; j < width; j++) {
          uint32_t xIndexInImage = xIndex - ((width-1)/2) + j;
          if (xIndexInImage >= 0 && xIndexInImage < image.width) {
              pixelRow.push_back(image.getGreyscalePixel(xIndexInImage, yIndexInImage));
           } else {
              pixelRow.push_back(Pixel(0,0,0,0));
           }
        }
        result.push_back(pixelRow);
        pixelRow.clear();
      }
      return result;
    }
};

#endif
