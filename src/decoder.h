#ifndef DECODER_H
#define DECODER_H

#include "image.h"
#include "lodepng/lodepng.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Decoder {
public:
  std::string input_filepath;
  uint32_t width, height;
  std::shared_ptr<Image> decodedImage;

  Decoder(std::string x) : 
    input_filepath(x) { 
      decode(); 
      decodedImage = std::make_shared<Image>(height, width, imageData);
    }

  Image getImage() { return Image(height, width, imageData); }

private:
  std::vector<uint8_t> imageData;
  void decode() {
    unsigned error = lodepng::decode(imageData, width, height, input_filepath);
    if (error) {
      std::cout << "decoder error " << error << ": "
                << lodepng_error_text(error) << '\n';
    }
  }
};

#endif
