#ifndef MEAN_BLUR_PROCESSOR
#define MEAN_BLUR_PROCESSOR

#include "image.h"
#include <cstdint>

class MeanBlurProcessor {
  public:
    Image image;
    MeanBlurProcessor(Image x): image(x) {};

    std::vector<std::vector<uint32_t>> meanBlurFilterData(uint32_t size) {
      std::vector<uint32_t> row(size, 1);
      return std::vector<std::vector<uint32_t>>(size, row);
    }; 

    //std::vector<uint8_t> process(){
     //}
};

#endif
