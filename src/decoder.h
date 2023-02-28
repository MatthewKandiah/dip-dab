#include "lodepng.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Decoder {
  public:
    std::string input_filepath;
    std::vector<unsigned char> image;
    unsigned width, height;

    Decoder(std::string x) {
      input_filepath = x;
      decode();
    }

  private:
    void decode() {
      unsigned error = lodepng::decode(image, width, height, input_filepath);
      if (error) {
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << '\n';
      }
    }
};

