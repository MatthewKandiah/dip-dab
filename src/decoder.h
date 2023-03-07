#ifndef DECODER_H
#define DECODER_H

#include "lodepng/lodepng.h"
#include "image.h"
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Decoder {
  public:
    std::string input_filepath;
    std::vector<uint8_t> imageData;
    unsigned width, height;

    Decoder(std::string x): input_filepath(x) {
      decode();
    }

    Image getImage(){
      return Image(height, width, imageData);
    }

  private:
    void decode() {
      unsigned error = lodepng::decode(imageData, width, height, input_filepath);
      if (error) {
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << '\n';
      }
    }
};

#endif
