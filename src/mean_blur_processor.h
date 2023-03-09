#ifndef MEAN_BLUR_PROCESSOR
#define MEAN_BLUR_PROCESSOR

#include "image.h"
#include <cstdint>

class MeanBlurProcessor {
  public:
    Image *image;
    MeanBlurProcessor(Image *x): image(x) {};

    //Image* process(){
     //}
};

#endif
