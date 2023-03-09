#ifndef ENCODER_H
#define ENCODER_H

#include "image.h"
#include "lodepng/lodepng.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Encoder {
public:
  std::string filename;
  Image *image;
  Encoder(std::string w, Image *x) : filename(w), image(x) {}

  void encode() {
    std::uint32_t error = lodepng::encode(filename, image->imageData,
                                          image->width, image->height);
    if (error) {
      std::cout << "encoder error " << error << ": "
                << lodepng_error_text(error) << '\n';
    } else {
      std::cout << "png image successfully written to " << filename << '\n';
    }
  }
};

#endif
